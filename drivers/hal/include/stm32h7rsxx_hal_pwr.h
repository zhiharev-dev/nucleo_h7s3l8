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

#ifndef STM32H7RSXX_HAL_PWR_H
#define STM32H7RSXX_HAL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "stm32h7rsxx_hal_def.h"

/* Exported macros --------------------------------------------------------- */

/* Exported constants ------------------------------------------------------ */

/* Конфигурация источника питания */
#define PWR_SUPPLY_DEFAULT                      (0x00000006UL)
#define PWR_SUPPLY_LDO                          (0x00000002UL)
#define PWR_SUPPLY_DIRECT_SMPS                  (0x00000004UL)
#define PWR_SUPPLY_EXTERNAL_SMPS_LDO            (0x0000001EUL)
#define PWR_SUPPLY_EXTERNAL_SMPS_LDO_BYPASS     (0x0000001DUL)
#define PWR_SUPPLY_BYPASS                       (0x00000001UL)

/* Уровень масштабирования напряжения */
#define PWR_VOS_LOW                             (0x00000000UL)
#define PWR_VOS_HIGH                            (0x00000001UL)

/* Состояние XSPIM2 */
#define PWR_XSPIM2_DISABLE                      (0x00000000UL)
#define PWR_XSPIM2_ENABLE                       (0x00008000UL)

/* Exported types ---------------------------------------------------------- */

/* Структура регистров PWR */
typedef PWR_TypeDef pwr_t;


/* Конфигурационная структура PWR */
typedef struct
{
    uint32_t supply;            /* Конфигурация источника питания */

    uint32_t vos;               /* Уровень масштабирования напряжения */

    uint32_t xspim2_enable;     /* Состояние XSPIM2 */
} pwr_config_t;

/* Exported variables ------------------------------------------------------ */

/* Exported function prototypes -------------------------------------------- */

void hal_pwr_init(const pwr_config_t * config);

/* Exported callback function prototypes ----------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7RSXX_HAL_PWR_H */
