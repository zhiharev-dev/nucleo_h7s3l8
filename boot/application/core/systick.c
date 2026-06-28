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

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

#define SYSTICK_IRQ_PRIORITY    (15U)

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/*
 * Инициализация SysTick
 *
 * Параметры: frequency - частота тактирования (гц)
 */
void systick_init(const uint32_t frequency)
{
    systick_config_t systick_config =
    {
        .frequency = frequency,
        .clksource = SYSTICK_CLKSOURCE_CPU,
    };

    hal_systick_init(&systick_config);
    hal_systick_start_it();

    NVIC_SetPriority(SysTick_IRQn, SYSTICK_IRQ_PRIORITY);
    NVIC_EnableIRQ(SysTick_IRQn);
}
/* ------------------------------------------------------------------------- */

/*
 * Текущее значение системного счетчика
 *
 * Возвращает: количество тиков с момента запуска системы (32-битное значение)
 */
inline uint32_t systick_get_ticks(void)
{
    return hal_systick_get_ticks();
}
/* ------------------------------------------------------------------------- */

/*
 * Задержка выполнения программы (блокирующий метод)
 *
 * Параметры: delay_ms - значение задержки (мс)
 */
inline void systick_delay(const uint32_t delay_ms)
{
    hal_systick_delay(delay_ms);
}
/* ------------------------------------------------------------------------- */
