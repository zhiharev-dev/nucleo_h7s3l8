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

#include "led.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

const led_t led_green =
{
    .gpio = &gpio_led_green,
    .active_state = LED_ACTIVE_HIGH,
};

const led_t led_yellow =
{
    .gpio = &gpio_led_yellow,
    .active_state = LED_ACTIVE_HIGH,
};

const led_t led_red =
{
    .gpio = &gpio_led_red,
    .active_state = LED_ACTIVE_HIGH,
};

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/*
 * Включение светодиода
 *
 * Параметры: self - указатель на структуру данных светодиода
 */
void led_on(const led_t * self)
{
    /* Проверка входных параметров */
    assert(self != NULL);

    /* Установка состояния вывода GPIO  */
    gpio_write_pin(self->gpio, self->active_state);
}
/* ------------------------------------------------------------------------- */

/*
 * Выключение светодиода
 *
 * Параметры: self - указатель на структуру данных светодиода
 */
void led_off(const led_t * self)
{
    /* Проверка входных параметров */
    assert(self != NULL);

    /* Установка состояния вывода GPIO  */
    gpio_write_pin(self->gpio, (self->active_state == LED_ACTIVE_HIGH) ? GPIO_RESET : GPIO_SET);
}
/* ------------------------------------------------------------------------- */

/*
 * Переключение состояния светодиода
 *
 * Параметры: self - указатель на структуру данных светодиода
 */
void led_toggle(const led_t * self)
{
    /* Проверка входных параметров */
    assert(self != NULL);

    /* Переключение состояния вывода GPIO  */
    gpio_toggle_pin(self->gpio);
}
/* ------------------------------------------------------------------------- */
