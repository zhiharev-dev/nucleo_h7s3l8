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

#ifndef GPIO_H
#define GPIO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "stm32h7rsxx_hal_gpio.h"

/* Exported macros --------------------------------------------------------- */

/* Exported constants ------------------------------------------------------ */

/* Exported types ---------------------------------------------------------- */

/* Exported variables ------------------------------------------------------ */

extern gpio_handle_t gpio_led_green;
extern gpio_handle_t gpio_led_yellow;
extern gpio_handle_t gpio_led_red;

/* Exported function prototypes -------------------------------------------- */

void gpio_init(void);

void gpio_set(gpio_handle_t * handle);

void gpio_reset(gpio_handle_t * handle);

void gpio_write_pin(gpio_handle_t * handle, uint32_t state);

uint32_t gpio_read_pin(gpio_handle_t * handle);

void gpio_toggle_pin(gpio_handle_t * handle);

/* Exported callback function prototypes ----------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPIO_H */
