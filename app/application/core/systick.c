/*
 * Copyright (C) 2026 zhiharev-dev <zhiharev.dev@mail.ru>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

/* Includes ---------------------------------------------------------------- */

#include "systick.h"

/* Constants --------------------------------------------------------------- */

/* Частота прерывания SysTick */
#define SYSTICK_TICK_FREQUENCY_HZ   (1000U)

/* Максимальное значение для 24-разрядного счетчика SysTick */
#define SYSTICK_MAX_LOAD_VALUE      (0xFFFFFFUL)

/* Приоритет прерывания SysTick */
#define SYSTICK_IRQ_PRIORITY        (15U)

/* Variables --------------------------------------------------------------- */

/* Системный счетчик, мс */
__attribute__((section(".dtcm_data")))
static volatile uint32_t ticks = 0U;

/* User code --------------------------------------------------------------- */

void systick_init(const uint32_t frequency)
{
    /* Проверка частоты тактирования SysTick */
    assert(frequency >= SYSTICK_TICK_FREQUENCY_HZ);

    /* Расчет и проверка значения перезагрузки счетчика SysTick */
    uint32_t load_value = (frequency / SYSTICK_TICK_FREQUENCY_HZ) - 1U;
    assert(load_value <= SYSTICK_MAX_LOAD_VALUE);

    /* Запрет прерываний (начало критической секции) */
    uint32_t primask = __get_PRIMASK();
    __disable_irq();

    /* Сброс параметров SysTick */
    SysTick->CTRL = 0U;
    /* Сброс счетчика SysTick */
    SysTick->VAL = 0U;
    /* Установка значения перезагрузки счетчика SysTick */
    SysTick->LOAD = load_value;
    /* Настройка и запуск SysTick */
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk;

    /* Сброс системного счетчика */
    ticks = 0U;

    /* Настройка прерывания SysTick в NVIC */
    NVIC_SetPriority(SysTick_IRQn, SYSTICK_IRQ_PRIORITY);
    NVIC_EnableIRQ(SysTick_IRQn);

    /* Синхронизация памяти */
    __DSB();
    __ISB();

    /* Восстановление прерываний (завершение критической секции) */
    __set_PRIMASK(primask);
}
/* ------------------------------------------------------------------------- */

__attribute__((section(".itcm_code")))
void systick_it_handler(void)
{
    ticks++;
    systick_period_elapsed_callback();
}
/* ------------------------------------------------------------------------- */

uint32_t systick_get_ticks(void)
{
    return ticks;   /* Атомарно - переменная (32-бит) резмещена в DTCM */
}
/* ------------------------------------------------------------------------- */

void systick_delay(const uint32_t delay_ms)
{
    /* Проверка входного параметра и состояния SysTick */
    if ((delay_ms == 0U) || ((SysTick->CTRL & SysTick_CTRL_ENABLE_Msk) == 0U)) {
        return;
    }

    /* Задержка выполнения программы */
    bool interrupts_enabled = (__get_PRIMASK() == 0U);
    uint32_t tick_start = systick_get_ticks();

    do {
        if (interrupts_enabled) {
            __WFI();    /* Ожидание прерывания (энергосбережение) */
        } else {
            __NOP();
        }
    } while ((systick_get_ticks() - tick_start) < delay_ms);
}
/* ------------------------------------------------------------------------- */

__attribute__((weak, section(".itcm_code")))
void systick_period_elapsed_callback(void)
{
    /* Пустая реализация */
}
/* ------------------------------------------------------------------------- */
