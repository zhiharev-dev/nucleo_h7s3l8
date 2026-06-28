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

#ifndef LED_H
#define LED_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "main.h"
#include "gpio.h"

/* Exported macros --------------------------------------------------------- */

/* Exported constants ------------------------------------------------------ */

/* Exported types ---------------------------------------------------------- */

/* Состояние активности светодиода */
typedef enum
{
    LED_ACTIVE_HIGH = GPIO_SET,
    LED_ACTIVE_LOW  = GPIO_RESET,
} led_active_state_t;


/* Структура данных светодиода */
typedef struct
{
    gpio_handle_t * gpio;       /* Указатель на структуру обработчика GPIO */

    uint8_t active_state;       /* Состояние активности светодиода */
} led_t;

/* Exported variables ------------------------------------------------------ */

extern const led_t led_green;
extern const led_t led_yellow;
extern const led_t led_red;

/* Exported function prototypes -------------------------------------------- */

void led_on(const led_t * self);

void led_off(const led_t * self);

void led_toggle(const led_t * self);

/* Exported callback function prototypes ----------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LED_H */
