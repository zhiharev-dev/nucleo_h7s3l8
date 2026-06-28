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

#include "stm32h7rsxx_hal_gpio.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/*
 * Инициализация GPIO
 *
 * Параметры:
 *     handle - указатель на структуру обработчика GPIO
 *     config - указатель на конфигурационную структуру GPIO
 */
void hal_gpio_init(gpio_handle_t * handle, const gpio_config_t * config)
{
    /* Проверка входных параметров */
    assert(handle != NULL);
    assert(handle->instance != NULL);
    assert(config != NULL);
    assert(config->af_nb <= 15U);

    /* Получение указателя на структуру GPIO */
    gpio_t * instance = handle->instance;

    /* Получение номера вывода */
    uint32_t pin = handle->pin;

    /* Настройка режима работы */
    instance->MODER = (instance->MODER & ~HAL_BIT_SHIFT(0x3U, pin * 2U)) |
                      HAL_BIT_SHIFT(config->mode, pin * 2U);

    /* Настройка типа выхода */
    instance->OTYPER = (instance->OTYPER & ~HAL_BIT_SHIFT(0x1U, pin * 1U)) |
                       HAL_BIT_SHIFT(config->output_type, pin * 1U);

    /* Настройка скорости переключения выхода */
    instance->OSPEEDR = (instance->OSPEEDR & ~HAL_BIT_SHIFT(0x3U, pin * 2U)) |
                        HAL_BIT_SHIFT(config->output_speed, pin * 2U);

    /* Настройка типа подтяжки вывода */
    instance->PUPDR = (instance->PUPDR & ~HAL_BIT_SHIFT(0x3U, pin * 2U)) |
                      HAL_BIT_SHIFT(config->pull, pin * 2U);

    /* Настройка номера альтернативной функции вывода */
    if (pin < GPIO_PIN8)
    {
        instance->AFR[0] = (instance->AFR[0] & ~HAL_BIT_SHIFT(0xFU, pin * 4U)) |
                           HAL_BIT_SHIFT(config->af_nb, pin * 4U);
    }
    else
    {
        instance->AFR[1] = (instance->AFR[1] & ~HAL_BIT_SHIFT(0xFU, (pin - 8U) * 4U)) |
                           HAL_BIT_SHIFT(config->af_nb, (pin - 8U) * 4U);
    }
}
/* ------------------------------------------------------------------------- */

/*
 * Установка состояния SET вывода GPIO
 *
 * Параметры: handle - указатель на структуру обработчика GPIO
 */
void hal_gpio_set(gpio_handle_t * handle)
{
    /* Проверка входных параметров */
    assert(handle != NULL);
    assert(handle->instance != NULL);

    /* Получение указателя на структуру GPIO */
    gpio_t * instance = handle->instance;

    /* Установка состояния SET вывода GPIO */
    instance->BSRR = HAL_BIT_MASK(handle->pin);
}
/* ------------------------------------------------------------------------- */

/*
 * Установка состояния RESET вывода GPIO
 *
 * Параметры: handle - указатель на структуру обработчика GPIO
 */
void hal_gpio_reset(gpio_handle_t * handle)
{
    /* Проверка входных параметров */
    assert(handle != NULL);
    assert(handle->instance != NULL);

    /* Получение указателя на структуру GPIO */
    gpio_t * instance = handle->instance;

    /* Установка состояния RESET вывода GPIO */
    instance->BSRR = HAL_BIT_SHIFT(HAL_BIT_MASK(handle->pin), 16U);
}
/* ------------------------------------------------------------------------- */

/*
 * Установка состояния вывода GPIO
 *
 * Параметры:
 *     handle - указатель на структуру обработчика GPIO
 *     state - состояние вывода GPIO
 */
void hal_gpio_write_pin(gpio_handle_t * handle, uint32_t state)
{
    /* Проверка входных параметров */
    assert(handle != NULL);
    assert(handle->instance != NULL);

    /* Установка состояния GPIO */
    if (state == GPIO_SET)
    {
        hal_gpio_set(handle);
    }
    else
    {
        hal_gpio_reset(handle);
    }
}
/* ------------------------------------------------------------------------- */

/*
 * Чтение состояния вывода GPIO
 *
 * Параметры: handle - указатель на структуру обработчика GPIO
 *
 * Возвращает: состояние вывода GPIO
 */
uint32_t hal_gpio_read_pin(gpio_handle_t * handle)
{
    /* Проверка входных параметров */
    assert(handle != NULL);
    assert(handle->instance != NULL);

    /* Получение указателя на структуру GPIO */
    gpio_t * instance = handle->instance;

    return (instance->IDR & HAL_BIT_MASK(handle->pin)) ? GPIO_SET : GPIO_RESET;
}
/* ------------------------------------------------------------------------- */

/*
 * Переключение состояния вывода GPIO (инвертирование)
 *
 * Параметры: handle - указатель на структуру обработчика GPIO
 */
void hal_gpio_toggle_pin(gpio_handle_t * handle)
{
    /* Проверка входных параметров */
    assert(handle != NULL);
    assert(handle->instance != NULL);

    /* Получение указателя на структуру GPIO */
    gpio_t * instance = handle->instance;

    /* Сохранение текущего состояния прерываний */
    uint32_t _pm = __get_PRIMASK();

    /* Запрет прерываний для атомарного переключения состояния */
    __disable_irq();

    /* Атомарное переключение состояния вывода */
    instance->ODR ^= HAL_BIT_MASK(handle->pin);

    /* Восстановление исходного состояния прерываний */
    __set_PRIMASK(_pm);
}
/* ------------------------------------------------------------------------- */
