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

#ifndef STM32H7RSXX_HAL_GPIO_H
#define STM32H7RSXX_HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "stm32h7rsxx_hal_def.h"

/* Exported macros --------------------------------------------------------- */

/* Включение тактирования GPIOA */
#define HAL_GPIOA_ENABLE_CLOCK() \
    (RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN_Msk)

/* Включение тактирования GPIOB */
#define HAL_GPIOB_ENABLE_CLOCK() \
    (RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN_Msk)

/* Включение тактирования GPIOC */
#define HAL_GPIOC_ENABLE_CLOCK() \
    (RCC->AHB4ENR |= RCC_AHB4ENR_GPIOCEN_Msk)

/* Включение тактирования GPIOD */
#define HAL_GPIOD_ENABLE_CLOCK() \
    (RCC->AHB4ENR |= RCC_AHB4ENR_GPIODEN_Msk)

/* Включение тактирования GPIOE */
#define HAL_GPIOE_ENABLE_CLOCK() \
    (RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN_Msk)

/* Включение тактирования GPIOF */
#define HAL_GPIOF_ENABLE_CLOCK() \
    (RCC->AHB4ENR |= RCC_AHB4ENR_GPIOFEN_Msk)

/* Включение тактирования GPIOG */
#define HAL_GPIOG_ENABLE_CLOCK() \
    (RCC->AHB4ENR |= RCC_AHB4ENR_GPIOGEN_Msk)

/* Включение тактирования GPIOH */
#define HAL_GPIOH_ENABLE_CLOCK() \
    (RCC->AHB4ENR |= RCC_AHB4ENR_GPIOHEN_Msk)

/* Включение тактирования GPIOM */
#define HAL_GPIOM_ENABLE_CLOCK() \
    (RCC->AHB4ENR |= RCC_AHB4ENR_GPIOMEN_Msk)

/* Включение тактирования GPION */
#define HAL_GPION_ENABLE_CLOCK() \
    (RCC->AHB4ENR |= RCC_AHB4ENR_GPIONEN_Msk)

/* Включение тактирования GPIOO */
#define HAL_GPIOO_ENABLE_CLOCK() \
    (RCC->AHB4ENR |= RCC_AHB4ENR_GPIOOEN_Msk)

/* Включение тактирования GPIOP */
#define HAL_GPIOP_ENABLE_CLOCK() \
    (RCC->AHB4ENR |= RCC_AHB4ENR_GPIOPEN_Msk)

/* Exported constants ------------------------------------------------------ */

/* Номера выводов GPIO */
#define GPIO_PIN0               (0x00000000UL)
#define GPIO_PIN1               (0x00000001UL)
#define GPIO_PIN2               (0x00000002UL)
#define GPIO_PIN3               (0x00000003UL)
#define GPIO_PIN4               (0x00000004UL)
#define GPIO_PIN5               (0x00000005UL)
#define GPIO_PIN6               (0x00000006UL)
#define GPIO_PIN7               (0x00000007UL)
#define GPIO_PIN8               (0x00000008UL)
#define GPIO_PIN9               (0x00000009UL)
#define GPIO_PIN10              (0x0000000AUL)
#define GPIO_PIN11              (0x0000000BUL)
#define GPIO_PIN12              (0x0000000CUL)
#define GPIO_PIN13              (0x0000000DUL)
#define GPIO_PIN14              (0x0000000EUL)
#define GPIO_PIN15              (0x0000000FUL)

/* Состояние вывода GPIO */
#define GPIO_RESET              (0x00000000UL)
#define GPIO_SET                (0x00000001UL)

/* Режим работы вывода GPIO */
#define GPIO_INPUT              (0x00000000UL)
#define GPIO_OUTPUT             (0x00000001UL)
#define GPIO_AF                 (0x00000002UL)
#define GPIO_ANALOG             (0x00000003UL)

/* Тип выхода GPIO */
#define GPIO_PUSH_PULL          (0x00000000UL)
#define GPIO_OPEN_DRAIN         (0x00000001UL)

/* Скорость переключения выхода GPIO */
#define GPIO_LOW_SPEED          (0x00000000UL)
#define GPIO_MEDIUM_SPEED       (0x00000001UL)
#define GPIO_HIGH_SPEED         (0x00000002UL)
#define GPIO_VERY_HIGH_SPEED    (0x00000003UL)

/* Тип подтяжки вывода GPIO */
#define GPIO_NO_PULL            (0x00000000UL)
#define GPIO_PULL_UP            (0x00000001UL)
#define GPIO_PULL_DOWN          (0x00000002UL)

/* Exported types ---------------------------------------------------------- */

/* Структура регистров GPIO */
typedef GPIO_TypeDef gpio_t;


/* Конфигурационная структура GPIO  */
typedef struct
{
    uint32_t mode;              /* Режим работы */

    uint32_t output_type;       /* Тип выхода */

    uint32_t output_speed;      /* Скорость переключения выхода */

    uint32_t pull;              /* Тип подтяжки */

    uint32_t af_nb;             /* Номер альтернативной функции, диапазон значений: 0-15 */
} gpio_config_t;


/* Структура обработчика GPIO */
typedef struct
{
    gpio_t * instance;      /* Указатель на структуру GPIO */

    uint32_t pin;           /* Номер вывода GPIO */
} gpio_handle_t;

/* Exported variables ------------------------------------------------------ */

/* Exported function prototypes -------------------------------------------- */

void hal_gpio_init(gpio_handle_t * handle, const gpio_config_t * config);

void hal_gpio_set(gpio_handle_t * handle);

void hal_gpio_reset(gpio_handle_t * handle);

void hal_gpio_write_pin(gpio_handle_t * handle, uint32_t state);

uint32_t hal_gpio_read_pin(gpio_handle_t * handle);

void hal_gpio_toggle_pin(gpio_handle_t * handle);

/* Exported callback function prototypes ----------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7RSXX_HAL_GPIO_H */
