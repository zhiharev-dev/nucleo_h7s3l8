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

#ifndef STM32H7RSXX_HAL_RCC_H
#define STM32H7RSXX_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "stm32h7rsxx_hal_def.h"

/* Exported macros --------------------------------------------------------- */

/* Exported constants ------------------------------------------------------ */

/* Состояние HSE */
#define RCC_HSE_DISABLE             (0x00000000UL)
#define RCC_HSE_ENABLE              (0x00010000UL)

/* Состояние HSE CSS */
#define RCC_HSE_CSS_DISABLE         (0x00000000UL)
#define RCC_HSE_CSS_ENABLE          (0x00100000UL)

/* Состояние LSE */
#define RCC_LSE_DISABLE             (0x00000000UL)
#define RCC_LSE_ENABLE              (0x00000001UL)

/* Состояние LSE CSS */
#define RCC_LSE_CSS_DISABLE         (0x00000000UL)
#define RCC_LSE_CSS_ENABLE          (0x00000020UL)

/* Источник тактирования PLL */
#define RCC_PLL_CLKSOURCE_HSI       (0x00000000UL)
#define RCC_PLL_CLKSOURCE_CSI       (0x00000001UL)
#define RCC_PLL_CLKSOURCE_HSE       (0x00000002UL)
#define RCC_PLL_CLKSOURCE_NONE      (0x00000003UL)

/* Состояние PLL */
#define RCC_PLL1_DISABLE            (0x00000000UL)
#define RCC_PLL1_ENABLE             (0x01000000UL)

#define RCC_PLL2_DISABLE            (0x00000000UL)
#define RCC_PLL2_ENABLE             (0x04000000UL)

#define RCC_PLL3_DISABLE            (0x00000000UL)
#define RCC_PLL3_ENABLE             (0x10000000UL)

/* Диапазон VCO PLL */
#define RCC_PLL1_VCOH               (0x00000000UL)
#define RCC_PLL1_VCOL               (0x00000002UL)

#define RCC_PLL2_VCOH               (0x00000000UL)
#define RCC_PLL2_VCOL               (0x00001000UL)

#define RCC_PLL3_VCOH               (0x00000000UL)
#define RCC_PLL3_VCOL               (0x00800000UL)

/* Диапазон RGE PLL */
#define RCC_PLL1_RGE_1_2MHZ         (0x00000000UL)
#define RCC_PLL1_RGE_2_4MHZ         (0x00000008UL)
#define RCC_PLL1_RGE_4_8MHZ         (0x00000010UL)
#define RCC_PLL1_RGE_8_16MHZ        (0x00000018UL)

#define RCC_PLL2_RGE_1_2MHZ         (0x00000000UL)
#define RCC_PLL2_RGE_2_4MHZ         (0x00004000UL)
#define RCC_PLL2_RGE_4_8MHZ         (0x00008000UL)
#define RCC_PLL2_RGE_8_16MHZ        (0x0000C000UL)

#define RCC_PLL3_RGE_1_2MHZ         (0x00000000UL)
#define RCC_PLL3_RGE_2_4MHZ         (0x02000000UL)
#define RCC_PLL3_RGE_4_8MHZ         (0x04000000UL)
#define RCC_PLL3_RGE_8_16MHZ        (0x06000000UL)

/* Значение делителя CPU */
#define RCC_CPU_DIV1                (0x00000000UL)
#define RCC_CPU_DIV2                (0x00000008UL)
#define RCC_CPU_DIV4                (0x00000009UL)
#define RCC_CPU_DIV8                (0x0000000AUL)
#define RCC_CPU_DIV16               (0x0000000BUL)
#define RCC_CPU_DIV64               (0x0000000CUL)
#define RCC_CPU_DIV128              (0x0000000DUL)
#define RCC_CPU_DIV256              (0x0000000EUL)
#define RCC_CPU_DIV512              (0x0000000FUL)

/* Значение делителя AHB */
#define RCC_AHB_DIV1                (0x00000000UL)
#define RCC_AHB_DIV2                (0x00000008UL)
#define RCC_AHB_DIV4                (0x00000009UL)
#define RCC_AHB_DIV8                (0x0000000AUL)
#define RCC_AHB_DIV16               (0x0000000BUL)
#define RCC_AHB_DIV64               (0x0000000CUL)
#define RCC_AHB_DIV128              (0x0000000DUL)
#define RCC_AHB_DIV256              (0x0000000EUL)
#define RCC_AHB_DIV512              (0x0000000FUL)

/* Значение делителя APB1 */
#define RCC_APB1_DIV1               (0x00000000UL)
#define RCC_APB1_DIV2               (0x00000004UL)
#define RCC_APB1_DIV4               (0x00000005UL)
#define RCC_APB1_DIV8               (0x00000006UL)
#define RCC_APB1_DIV16              (0x00000007UL)

/* Значение делителя APB2 */
#define RCC_APB2_DIV1               (0x00000000UL)
#define RCC_APB2_DIV2               (0x00000040UL)
#define RCC_APB2_DIV4               (0x00000050UL)
#define RCC_APB2_DIV8               (0x00000060UL)
#define RCC_APB2_DIV16              (0x00000070UL)

/* Значение делителя APB4 */
#define RCC_APB4_DIV1               (0x00000000UL)
#define RCC_APB4_DIV2               (0x00000400UL)
#define RCC_APB4_DIV4               (0x00000500UL)
#define RCC_APB4_DIV8               (0x00000600UL)
#define RCC_APB4_DIV16              (0x00000700UL)

/* Значение делителя APB5 */
#define RCC_APB5_DIV1               (0x00000000UL)
#define RCC_APB5_DIV2               (0x00004000UL)
#define RCC_APB5_DIV4               (0x00005000UL)
#define RCC_APB5_DIV8               (0x00006000UL)
#define RCC_APB5_DIV16              (0x00007000UL)

/* Системный источник тактирования */
#define RCC_SYSTEM_CLKSOURCE_HSI    (0x00000000UL)
#define RCC_SYSTEM_CLKSOURCE_CSI    (0x00000001UL)
#define RCC_SYSTEM_CLKSOURCE_HSE    (0x00000002UL)
#define RCC_SYSTEM_CLKSOURCE_PLL1P  (0x00000003UL)

/* Источник тактирования XSPI2 */
#define RCC_XSPI2_CLKSOURCE_HCLK5   (0x00000000UL)
#define RCC_XSPI2_CLKSOURCE_PLL2S   (0x00000040UL)
#define RCC_XSPI2_CLKSOURCE_PLL2T   (0x00000080UL)

/* Exported types ---------------------------------------------------------- */

/* Структура регистров RCC */
typedef RCC_TypeDef rcc_t;


/* Конфигурационная структура PLL */
typedef struct
{
    uint32_t enable;    /* Состояние */

    uint32_t vco;       /* Диапазон VCO (генератора, управляемого напряжением) */

    uint32_t rge;       /* Диапазон RGE (рабочей частоты генератора) */

    uint32_t divn;      /* Множитель DIVN, диапазон допустимых значений: 8-420 */

    uint32_t divp;      /* Делитель DIVP, диапазон допустимых значений: 1-128 */

    uint32_t divq;      /* Делитель DIVQ, диапазон допустимых значений: 1-128 */

    uint32_t divr;      /* Делитель DIVR, диапазон допустимых значений: 1-128 */

    uint32_t divs;      /* Делитель DIVS, диапазон допустимых значений: 1-8 */

    uint32_t divt;      /* Делитель DIVT, диапазон допустимых значений: 1-8 */

    uint32_t fracn;     /* Дробная часть коэффициента умножения для VCO, диапазон: 0–8191 (13 бит) */
} rcc_pll_config_t;


/* Конфигурационная структура RCC */
typedef struct
{
    uint32_t hse_enable;            /* Состояние HSE */

    uint32_t hse_css_enable;        /* Состояние HSE CSS */

    uint32_t lse_enable;            /* Состояние LSE */

    uint32_t lse_css_enable;        /* Состояние LSE CSS */

    uint32_t pll_clksource;         /* Источник тактирования PLL */

    uint32_t pll_divm1;             /* Значение делителя PLL DIVM1, диапазон: 0–63 */

    uint32_t pll_divm2;             /* Значение делителя PLL DIVM2, диапазон: 0–63 */

    uint32_t pll_divm3;             /* Значение делителя PLL DIVM3, диапазон: 0–63 */

    rcc_pll_config_t pll1;          /* Конфигурационная структура PLL1 */

    rcc_pll_config_t pll2;          /* Конфигурационная структура PLL2 */

    rcc_pll_config_t pll3;          /* Конфигурационная структура PLL3 */

    uint32_t cpu_div;               /* Значение делителя частоты для ядра CPU */

    uint32_t ahb_div;               /* Значение делителя частоты для шины AHB */

    uint32_t apb1_div;              /* Значение делителя частоты для шины APB1 */

    uint32_t apb2_div;              /* Значение делителя частоты для шины APB2 */

    uint32_t apb4_div;              /* Значение делителя частоты для шины APB4 */

    uint32_t apb5_div;              /* Значение делителя частоты для шины APB5 */

    uint32_t system_clksource;      /* Системный источник тактирования */

    uint32_t xspi2_clksource;       /* Источник тактирования XSPI2 */
} rcc_config_t;

/* Exported variables ------------------------------------------------------ */

/* Exported function prototypes -------------------------------------------- */

void hal_rcc_init(const rcc_config_t * config);

/* Exported callback function prototypes ----------------------------------- */

__WEAK void hal_rcc_hserdy_timeout_callback(void);

__WEAK void hal_rcc_lserdy_timeout_callback(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7RSXX_HAL_RCC_H */
