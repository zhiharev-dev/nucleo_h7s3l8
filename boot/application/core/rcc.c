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

#include "rcc.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/* Инициализация RCC */
void rcc_init(void)
{
    rcc_config_t rcc_config =
    {
        .hse_enable = RCC_HSE_ENABLE,
        .hse_css_enable = RCC_HSE_CSS_ENABLE,
        .lse_enable = RCC_LSE_ENABLE,
        .lse_css_enable = RCC_LSE_CSS_ENABLE,

        .pll_clksource = RCC_PLL_CLKSOURCE_HSE,     /* 24 MHz */
        .pll_divm1 = 12,                            /* 24 MHz / 12 = 2 MHz */
        .pll_divm2 = 12,                            /* 24 MHz / 12 = 2 MHz */

        .pll1.enable = RCC_PLL1_ENABLE,
        .pll1.vco = RCC_PLL1_VCOH,
        .pll1.rge = RCC_PLL1_RGE_2_4MHZ,
        .pll1.divn = 300,                           /* 2 MHz * 300 = 600 MHz */
        .pll1.divp = 1,                             /* 600 MHz / 1 = 600 MHz */

        .pll2.enable = RCC_PLL2_ENABLE,
        .pll2.vco = RCC_PLL2_VCOH,
        .pll2.rge = RCC_PLL2_RGE_2_4MHZ,
        .pll2.divn = 300,                           /* 2 MHz * 300 = 600 MHz */
        .pll2.divt = 3,                             /* 600 MHz / 3 = 200 MHz */

        .cpu_div = RCC_CPU_DIV1,                    /* 600 MHz / 1 = 600 MHz */
        .ahb_div = RCC_AHB_DIV2,                    /* 600 MHz / 2 = 300 MHz */
        .apb1_div = RCC_APB1_DIV2,                  /* 300 MHz / 2 = 150 MHz */
        .apb2_div = RCC_APB2_DIV2,                  /* 300 MHz / 2 = 150 MHz */
        .apb4_div = RCC_APB4_DIV2,                  /* 300 MHz / 2 = 150 MHz */
        .apb5_div = RCC_APB5_DIV2,                  /* 300 MHz / 2 = 150 MHz */

        .system_clksource = RCC_SYSTEM_CLKSOURCE_PLL1P,
        .xspi2_clksource = RCC_XSPI2_CLKSOURCE_PLL2T,
    };

    hal_rcc_init(&rcc_config);
}
/* ------------------------------------------------------------------------- */
