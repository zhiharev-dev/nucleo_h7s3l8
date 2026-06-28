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

#ifndef STM32H7RSXX_HAL_DEF_H
#define STM32H7RSXX_HAL_DEF_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "stm32h7s3xx.h"

/* Exported macros --------------------------------------------------------- */

/* Сдвиг значения X на N бит (N: 0-31) */
#define HAL_BIT_SHIFT(x, n) \
    ((uint32_t)(((n) < 32U) ? ((uint32_t)(x) << (n)) : 0U))

/* Маска бита в позиции bit (bit: 0-31) */
#define HAL_BIT_MASK(bit) \
    ((uint32_t)(((bit) < 32U) ? (0x1UL << (bit)) : 0U))

/* Атомарное чтение переменной */
#define HAL_ATOMIC_READ(var, ret) \
    do { \
        uint32_t _pm = __get_PRIMASK(); \
        __disable_irq(); \
        (ret) = (var); \
        __set_PRIMASK(_pm); \
    } while(0)

/* Атомарная запись в переменную */
#define HAL_ATOMIC_WRITE(var, value) \
    do { \
        uint32_t _pm = __get_PRIMASK(); \
        __disable_irq(); \
        (var) = (value); \
        __set_PRIMASK(_pm); \
    } while(0)

/* Exported constants ------------------------------------------------------ */

/* Exported types ---------------------------------------------------------- */

/* Код возврата */
typedef enum
{
    HAL_OK      = 0U,
    HAL_ERROR   = 1U,
    HAL_BUSY    = 2U,
    HAL_TIMEOUT = 3U,
} hal_status_t;

/* Exported variables ------------------------------------------------------ */

/* Exported function prototypes -------------------------------------------- */

/* Exported callback function prototypes ----------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7RSXX_HAL_DEF_H */
