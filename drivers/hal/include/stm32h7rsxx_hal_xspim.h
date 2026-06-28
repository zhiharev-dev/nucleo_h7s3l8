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

#ifndef STM32H7RSXX_HAL_XSPIM_H
#define STM32H7RSXX_HAL_XSPIM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "stm32h7rsxx_hal_def.h"

/* Exported macros --------------------------------------------------------- */

/* Включение тактирования XSPIM */
#define HAL_XSPIM_ENABLE_CLOCK() \
    (RCC->AHB5ENR |= RCC_AHB5ENR_XSPIMEN_Msk)

/* Exported constants ------------------------------------------------------ */

/* Состояние режима мультиплексирования */
#define XSPIM_MUX_DISABLE           (0x00000000UL)
#define XSPIM_MUX_ENABLE            (0x00000001UL)

/* Режим мультиплексирования XSPIM */
#define XSPIM_MODE_DIRECT           (0x00000000UL)
#define XSPIM_MODE_SWAPPED          (0x00000002UL)
#define XSPIM_MODE_ARB_OUTPUT_P1    (0x00000000UL)
#define XSPIM_MODE_ARB_OUTPUT_P2    (0x00000002UL)

/* Состояние переопределение NCS */
#define XSPIM_OVR_NCS_DISABLE       (0x00000000UL)
#define XSPIM_OVR_NCS_ENABLE        (0x00000010UL)

/* Сигнал переопределения NCS */
#define XSPIM_OVR_NCS1_XSPI1        (0x00000000UL)
#define XSPIM_OVR_NCS2_XSPI1        (0x00000020UL)

#define XSPIM_OVR_NCS1_XSPI2        (0x00000000UL)
#define XSPIM_OVR_NCS2_XSPI2        (0x00000040UL)

/* Exported types ---------------------------------------------------------- */

/* Структура регистров XSPIM */
typedef XSPIM_TypeDef xspim_t;


/* Конфигурационная структура XSPIM */
typedef struct
{
    uint32_t mux_enable;                /* Состояние режима мультиплексирования */

    uint32_t mode;                      /* Режим мультиплексирования */

    uint32_t override_ncs_enable;       /* Состояние переопределение NCS */

    uint32_t override_ncs_xspi1;        /* Переопределение NCS для XSPI1 */

    uint32_t override_ncs_xspi2;        /* Переопределение NCS для XSPI2 */

    uint32_t req2ack_time;              /* Время между транзакциями в режиме мультиплексирования */
} xspim_config_t;

/* Exported variables ------------------------------------------------------ */

/* Exported function prototypes -------------------------------------------- */

void hal_xspim_init(const xspim_config_t * config);

/* Exported callback function prototypes ----------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7RSXX_HAL_XSPIM_H */
