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

#include "gpio.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

static void gpio_octospi_init(void);

/* Private user code ------------------------------------------------------- */

/* Инициализация GPIO */
void gpio_init(void)
{
    HAL_GPIOA_ENABLE_CLOCK();
    HAL_GPION_ENABLE_CLOCK();

    gpio_octospi_init();
}
/* ------------------------------------------------------------------------- */

/*
 * Установка состояния SET вывода GPIO
 *
 * Параметры: handle - указатель на структуру обработчика GPIO
 */
inline void gpio_set(gpio_handle_t * handle)
{
    hal_gpio_set(handle);
}
/* ------------------------------------------------------------------------- */

/*
 * Установка состояния RESET вывода GPIO
 *
 * Параметры: handle - указатель на структуру обработчика GPIO
 */
inline void gpio_reset(gpio_handle_t * handle)
{
    hal_gpio_reset(handle);
}
/* ------------------------------------------------------------------------- */

/*
 * Установка состояния вывода GPIO
 *
 * Параметры:
 *     handle - указатель на структуру обработчика GPIO
 *     state - состояние вывода GPIO
 */
inline void gpio_write_pin(gpio_handle_t * handle, uint32_t state)
{
    hal_gpio_write_pin(handle, state);
}
/* ------------------------------------------------------------------------- */

/*
 * Чтение состояния вывода GPIO
 *
 * Параметры: handle - указатель на структуру обработчика GPIO
 *
 * Возвращает: состояние вывода GPIO
 */
inline uint32_t gpio_read_pin(gpio_handle_t * handle)
{
    return hal_gpio_read_pin(handle);
}
/* ------------------------------------------------------------------------- */

/*
 * Переключение состояния вывода GPIO (инвертирование)
 *
 * Параметры: handle - указатель на структуру обработчика GPIO
 */
inline void gpio_toggle_pin(gpio_handle_t * handle)
{
    hal_gpio_toggle_pin(handle);
}
/* ------------------------------------------------------------------------- */

/* Инициализация GPIO OCTOSPI */
static void gpio_octospi_init(void)
{
    gpio_config_t gpio_config =
    {
        .mode = GPIO_AF,
        .output_type = GPIO_PUSH_PULL,
        .output_speed = GPIO_VERY_HIGH_SPEED,
        .pull = GPIO_NO_PULL,
        .af_nb = 9,
    };

    gpio_handle_t gpio_octospi_ncs =
    {
        .instance = GPION,
        .pin = GPIO_PIN1,
    };

    gpio_handle_t gpio_octospi_dqs =
    {
        .instance = GPION,
        .pin = GPIO_PIN0,
    };

    gpio_handle_t gpio_octospi_clk =
    {
        .instance = GPION,
        .pin = GPIO_PIN6,
    };

    gpio_handle_t gpio_octospi_io0 =
    {
        .instance = GPION,
        .pin = GPIO_PIN2,
    };

    gpio_handle_t gpio_octospi_io1 =
    {
        .instance = GPION,
        .pin = GPIO_PIN3,
    };

    gpio_handle_t gpio_octospi_io2 =
    {
        .instance = GPION,
        .pin = GPIO_PIN4,
    };

    gpio_handle_t gpio_octospi_io3 =
    {
        .instance = GPION,
        .pin = GPIO_PIN5,
    };

    gpio_handle_t gpio_octospi_io4 =
    {
        .instance = GPION,
        .pin = GPIO_PIN8,
    };

    gpio_handle_t gpio_octospi_io5 =
    {
        .instance = GPION,
        .pin = GPIO_PIN9,
    };

    gpio_handle_t gpio_octospi_io6 =
    {
        .instance = GPION,
        .pin = GPIO_PIN10,
    };

    gpio_handle_t gpio_octospi_io7 =
    {
        .instance = GPION,
        .pin = GPIO_PIN11,
    };

    hal_gpio_init(&gpio_octospi_ncs, &gpio_config);
    hal_gpio_init(&gpio_octospi_dqs, &gpio_config);
    hal_gpio_init(&gpio_octospi_clk, &gpio_config);
    hal_gpio_init(&gpio_octospi_io0, &gpio_config);
    hal_gpio_init(&gpio_octospi_io1, &gpio_config);
    hal_gpio_init(&gpio_octospi_io2, &gpio_config);
    hal_gpio_init(&gpio_octospi_io3, &gpio_config);
    hal_gpio_init(&gpio_octospi_io4, &gpio_config);
    hal_gpio_init(&gpio_octospi_io5, &gpio_config);
    hal_gpio_init(&gpio_octospi_io6, &gpio_config);
    hal_gpio_init(&gpio_octospi_io7, &gpio_config);
}
/* ------------------------------------------------------------------------- */
