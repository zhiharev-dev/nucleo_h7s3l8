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

#ifndef STM32H7RSXX_HAL_FLASH_H
#define STM32H7RSXX_HAL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "stm32h7rsxx_hal_def.h"

/* Exported macros --------------------------------------------------------- */

/* Exported constants ------------------------------------------------------ */

/* Задержка во время оцераций чтения */
#define FLASH_LATENCY_0WS           (0x00000000UL)
#define FLASH_LATENCY_1WS           (0x00000001UL)
#define FLASH_LATENCY_2WS           (0x00000002UL)
#define FLASH_LATENCY_3WS           (0x00000003UL)
#define FLASH_LATENCY_4WS           (0x00000004UL)
#define FLASH_LATENCY_5WS           (0x00000005UL)
#define FLASH_LATENCY_6WS           (0x00000006UL)
#define FLASH_LATENCY_7WS           (0x00000007UL)

/* Задержка во время операций программирования */
#define FLASH_WRHIGHFREQ0           (0x00000000UL)
#define FLASH_WRHIGHFREQ1           (0x00000010UL)
#define FLASH_WRHIGHFREQ2           (0x00000020UL)
#define FLASH_WRHIGHFREQ3           (0x00000030UL)

/* Распределение SRAM1 между ITCM или AXI SRAM */
#define FLASH_ITCM_AXI_SHARE_64K    (0x00000000UL)      /* ITCM = 64 Kb, AXI SRAM = 128 Kb */
#define FLASH_ITCM_AXI_SHARE_128K   (0x00000001UL)      /* ITCM = 128 Kb, AXI SRAM = 64 Kb */
#define FLASH_ITCM_AXI_SHARE_192K   (0x00000002UL)      /* ITCM = 192 Kb, AXI SRAM = 0 Kb */

/* Распределение SRAM3 между DTCM или AXI SRAM */
#define FLASH_DTCM_AXI_SHARE_64K    (0x00000000UL)      /* DTCM = 64 Kb, AXI SRAM = 128 Kb */
#define FLASH_DTCM_AXI_SHARE_128K   (0x00000010UL)      /* DTCM = 128 Kb, AXI SRAM = 64 Kb */
#define FLASH_DTCM_AXI_SHARE_192K   (0x00000020UL)      /* DTCM = 192 Kb, AXI SRAM = 0 Kb */

/* Распределение SRAM4 между ECC или AXI SRAM */
#define FLASH_ECC_ON_SRAM_DISABLE   (0x00000000UL)      /* ECC = 0 Kb, AXI SRAM = 72 Kb */
#define FLASH_ECC_ON_SRAM_ENABLE    (0x00000100UL)      /* ECC = 72 Kb, AXI SRAM = 0 Kb */

/* Состояние High Speed Low Voltage XSPI2 */
#define FLASH_XSPI2_HSLV_DISABLE    (0x00000000UL)
#define FLASH_XSPI2_HSLV_ENABLE     (0x00000200UL)

/* Exported types ---------------------------------------------------------- */

/* Структура регистров FLASH */
typedef FLASH_TypeDef flash_t;


/* Конфигурационная структура FLASH */
typedef struct
{
    uint32_t latency;       /* Задержка во время оцераций чтения */

    uint32_t wrhighfreq;    /* Задержка во время операций программирования */
} flash_config_t;


/* Конфигурационная структура опций FLASH */
typedef struct
{
    uint32_t itcm_axi_share;        /* Распределение SRAM1 между ITCM или AXI SRAM */

    uint32_t dtcm_axi_share;        /* Распределение SRAM3 между DTCM или AXI SRAM */

    uint32_t ecc_on_sram;           /* Распределение SRAM4 между ECC или AXI SRAM */

    uint32_t xspi2_hslv_enable;     /* Состояние High Speed Low Voltage XSPI2 */
} flash_opt_config_t;

/* Exported variables ------------------------------------------------------ */

/* Exported function prototypes -------------------------------------------- */

void hal_flash_init(const flash_config_t * config);

void hal_flash_opt_init(const flash_opt_config_t * config);

/* Exported callback function prototypes ----------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7RSXX_HAL_FLASH_H */
