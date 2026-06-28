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

#include "stm32h7rsxx_hal_systick.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Максимальное значение перезагрузки счетчика SysTick */
#define SYSTICK_MAX_RELOAD_VALUE    (0xFFFFFFUL)

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Системный счетчик (мс) */
static volatile uint32_t ticks = 0U;

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/*
 * Инициализация SysTick
 *
 * Параметры: config - указатель на конфигурационную структуру SysTick
 */
void hal_systick_init(const systick_config_t * config)
{
    /* Проверка входных параметров */
    assert(config != NULL);
    assert(config->frequency >= 1000U);

    /* Расчёт значения перезагрузки счётчика SysTick */
    uint32_t load_value = (config->frequency / 1000U) - 1U;

    /* Проверка значения перезагрузки счетчика SysTick */
    assert(SYSTICK_MAX_RELOAD_VALUE > load_value);

    /* Сброс регистра управления SysTick */
    SysTick->CTRL = 0U;

    /* Установка значения перезагрузки счётчика SysTick */
    SysTick->LOAD = load_value;

    /* Настройка параметров SysTick */
    SysTick->CTRL = config->clksource;

    /* Сброс значения системного счетчика */
    ticks = 0U;
}
/* ------------------------------------------------------------------------- */

/* Обработка прерываний SysTick */
void hal_systick_it_handler(void)
{
    /* Увеличение счетчика тиков */
    ticks++;

    /* Вызов пользовательского колбэка */
    hal_systick_period_elapsed_callback();
}
/* ------------------------------------------------------------------------- */

/* Запуск SysTick с включением прерываний */
void hal_systick_start_it(void)
{
    /* Сброс счётчика */
    SysTick->VAL = 0U;

    /* Включение прерываний и запуск SysTick */
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}
/* ------------------------------------------------------------------------- */

/* Останов SysTick */
void hal_systick_stop_it(void)
{
    /* Отключение прерываний и остановка SysTick */
    SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
}
/* ------------------------------------------------------------------------- */

/*
 * Текущее значение системного счетчика
 *
 * Возвращает: количество тиков с момента запуска системы (32-битное значение)
 */
uint32_t hal_systick_get_ticks(void)
{
    uint32_t ret_ticks;

    HAL_ATOMIC_READ(ticks, ret_ticks);

    return ret_ticks;
}
/* ------------------------------------------------------------------------- */

/*
 * Задержка выполнения программы (блокирующий метод)
 *
 * Параметры: delay_ms - значение задержки (мс)
 */
void hal_systick_delay(const uint32_t delay_ms)
{
    uint32_t tick_start;

    /* Проверка входного параметра */
    if (delay_ms == 0U)
    {
        /* Нулевая задержка - немедленный возврат */
        return;
    }

    /* Проверка состояния таймера */
    if ((SysTick->CTRL & SysTick_CTRL_ENABLE_Msk) == 0U)
    {
        /* Таймер выключен - немедленный возврат */
        return;
    }

    /* Получение начального значения счетчика */
    tick_start = hal_systick_get_ticks();

    /* Задержка выполнения программы с переходом в энергосберегающий режим */
    do
    {
        __WFI();
    }
    while ((hal_systick_get_ticks() - tick_start) < delay_ms);
}
/* ------------------------------------------------------------------------- */

__WEAK void hal_systick_period_elapsed_callback(void)
{

}
/* ------------------------------------------------------------------------- */
