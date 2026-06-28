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

#ifndef STM32H7RSXX_HAL_SYSTICK_H
#define STM32H7RSXX_HAL_SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "stm32h7rsxx_hal_def.h"

/* Exported macros --------------------------------------------------------- */

/* Exported constants ------------------------------------------------------ */

/* Источник тактирования SysTick */
#define SYSTICK_CLKSOURCE_CPU_DIV8      (0x00000000UL)
#define SYSTICK_CLKSOURCE_CPU           (0x00000004UL)

/* Exported types ---------------------------------------------------------- */

/* Структура регистров SysTick */
typedef SysTick_Type systick_t;


/* Конфигурационная структура SysTick */
typedef struct
{
    uint32_t frequency;     /* Частота тактирования (Гц) */

    uint32_t clksource;     /* Источник тактирования */
} systick_config_t;

/* Exported variables ------------------------------------------------------ */

/* Exported function prototypes -------------------------------------------- */

void hal_systick_init(const systick_config_t * config);

void hal_systick_it_handler(void);

void hal_systick_start_it(void);

void hal_systick_stop_it(void);

uint32_t hal_systick_get_ticks(void);

void hal_systick_delay(const uint32_t delay_ms);

/* Exported callback function prototypes ----------------------------------- */

__WEAK void hal_systick_period_elapsed_callback(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7RSXX_HAL_SYSTICK_H */
