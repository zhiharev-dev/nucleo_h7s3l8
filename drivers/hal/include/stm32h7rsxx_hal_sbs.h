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

#ifndef STM32H7RSXX_HAL_SBS_H
#define STM32H7RSXX_HAL_SBS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "stm32h7rsxx_hal_def.h"

/* Exported macros --------------------------------------------------------- */

/* Включение тактирование SBS */
#define HAL_SBS_ENABLE_CLOCK() \
    (RCC->APB4ENR |= RCC_APB4ENR_SBSEN_Msk)

/* Exported constants ------------------------------------------------------ */

/* Состояние IO High Speed Low Voltage XSPI2 */
#define SBS_XSPI2_IOHSLV_DISABLE    (0x00000000UL)
#define SBS_XSPI2_IOHSLV_ENABLE     (0x00040000UL)

/* Exported types ---------------------------------------------------------- */

/* Структура регистров SBS */
typedef SBS_TypeDef sbs_t;


/* Конфигурационная структура SBS */
typedef struct
{
    uint32_t xspi2_iohslv_enable;   /* Состояние IO High Speed Low Voltage XSPI2 */
} sbs_config_t;

/* Exported variables ------------------------------------------------------ */

/* Exported function prototypes -------------------------------------------- */

void hal_sbs_init(const sbs_config_t * config);

/* Exported callback function prototypes ----------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7RSXX_HAL_SBS_H */
