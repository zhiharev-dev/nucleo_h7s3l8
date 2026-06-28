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

#include "stm32h7rsxx_hal_rcc.h"
#include "stm32h7rsxx_hal_systick.h"

/* Private macros ---------------------------------------------------------- */

/* Проверка диапазона */
#define HAL_RCC_IS_IN_RANGE(value, min, max) \
    (((value) >= (min)) && ((value) <= (max)))

/* Значение PLL DIVM1 регистра PLLCKSELR (с проверкой диапазона) */
#define HAL_RCC_PLLCKSELR_DIVM1(div) \
    ((HAL_RCC_IS_IN_RANGE(div, 0U, 63U)) ? \
     ((div) << RCC_PLLCKSELR_DIVM1_Pos) : 0U)

/* Значение PLL DIVM2 регистра PLLCKSELR (с проверкой диапазона) */
#define HAL_RCC_PLLCKSELR_DIVM2(div) \
    ((HAL_RCC_IS_IN_RANGE(div, 0U, 63U)) ? \
     ((div) << RCC_PLLCKSELR_DIVM2_Pos) : 0U)

/* Значение PLL DIVM3 регистра PLLCKSELR (с проверкой диапазона) */
#define HAL_RCC_PLLCKSELR_DIVM3(div) \
    ((HAL_RCC_IS_IN_RANGE(div, 0U, 63U)) ? \
     ((div) << RCC_PLLCKSELR_DIVM3_Pos) : 0U)

/* Private constants ------------------------------------------------------- */

/* Таймаут ожидания готовности HSE и LSE */
#define RCC_HSERDY_TIMEOUT  (100U)
#define RCC_LSERDY_TIMEOUT  (5000U)

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/*
 * Инициализация RCC
 *
 * Параметры: config - указатель на конфигурационную структуру RCC
 */
void hal_rcc_init(const rcc_config_t * config)
{
    /* Проверка входных параметров */
    assert(config != NULL);

    /* HSE ----------------------------------------------------------------- */

    /* Сброс состояния HSE и CSS */
    RCC->CR &= ~(RCC_CR_HSEON_Msk | RCC_CR_HSECSSON_Msk);

    if (config->hse_enable == RCC_HSE_ENABLE)
    {
        /* Включение HSE */
        RCC->CR |= config->hse_enable;

        /* Ожидание готовности HSE */
        uint32_t tick_start = hal_systick_get_ticks();

        while ((RCC->CR & RCC_CR_HSERDY_Msk) == 0U)
        {
            if (hal_systick_get_ticks() - tick_start > RCC_HSERDY_TIMEOUT)
            {
                hal_rcc_hserdy_timeout_callback();
            }
        }

        /* Установка состояния CSS */
        RCC->CR |= config->hse_css_enable;
    }

    /* LSE ----------------------------------------------------------------- */

    /* Сброс состояния LSE и CSS */
    RCC->BDCR &= ~(RCC_BDCR_LSEON_Msk | RCC_BDCR_LSECSSON_Msk);

    if (config->lse_enable == RCC_LSE_ENABLE)
    {
        /* Включение LSE */
        RCC->BDCR |= config->lse_enable;

        /* Ожидание готовности LSE */
        uint32_t tick_start = hal_systick_get_ticks();

        while ((RCC->BDCR & RCC_BDCR_LSERDY_Msk) == 0U)
        {
            if (hal_systick_get_ticks() - tick_start > RCC_LSERDY_TIMEOUT)
            {
                hal_rcc_lserdy_timeout_callback();
            }
        }

        /* Установка состояния CSS */
        RCC->BDCR |= config->lse_css_enable;
    }

    /* PLL ----------------------------------------------------------------- */

    /* Сброс состояния PLL */
    RCC->CR &= ~(RCC_CR_PLL1ON_Msk | RCC_CR_PLL2ON_Msk | RCC_CR_PLL3ON_Msk);

    /* Проверка соответствия источника тактирования PLL и состояния HSE */
    if (config->pll_clksource == RCC_PLL_CLKSOURCE_HSE)
    {
        assert(config->hse_enable == RCC_HSE_ENABLE);
    }

    /* Настройка источника тактирования, значения делителей PLL DIVM1..3 */
    RCC->PLLCKSELR = config->pll_clksource                      |
                     HAL_RCC_PLLCKSELR_DIVM1(config->pll_divm1) |
                     HAL_RCC_PLLCKSELR_DIVM2(config->pll_divm2) |
                     HAL_RCC_PLLCKSELR_DIVM2(config->pll_divm3);

    /* Настройка диапазонов VCO и RGE, отключение делителей PLL */
    RCC->PLLCFGR = config->pll1.vco |
                   config->pll1.rge |
                   config->pll2.vco |
                   config->pll2.rge |
                   config->pll3.vco |
                   config->pll3.rge;

    /* PLL1 ---------------------------------------------------------------- */

    /* Сброс PLL1DIVR1 и PLL1DIVR2 */
    RCC->PLL1DIVR1 = 0U;
    RCC->PLL1DIVR2 = 0U;

    /* DIVN */
    if (config->pll1.divn < 8U || config->pll1.divn > 420U)
    {
        /* Установка значения DIVN по умолчанию */
        RCC->PLL1DIVR1 |= 0x80U;
    }
    else
    {
        /* Установка значения DIVN */
        RCC->PLL1DIVR1 |= ((config->pll1.divn - 1U) << RCC_PLL1DIVR1_DIVN_Pos);
    }

    /* DIVP */
    if (config->pll1.divp == 0U || config->pll1.divp == 3U || config->pll1.divp > 128U)
    {
        /* Установка значения DIVP по умолчанию */
        RCC->PLL1DIVR1 |= 0x200U;
    }
    else
    {
        /* Установка значения DIVP */
        RCC->PLL1DIVR1 |= ((config->pll1.divp - 1U) << RCC_PLL1DIVR1_DIVP_Pos);

        /* Включение DIVP */
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL1PEN_Msk;
    }

    /* DIVQ */
    if (config->pll1.divq == 0U || config->pll1.divq > 128U)
    {
        /* Установка значения DIVQ по умолчанию */
        RCC->PLL1DIVR1 |= 0x10000U;
    }
    else
    {
        /* Установка значения DIVQ */
        RCC->PLL1DIVR1 |= ((config->pll1.divq - 1U) << RCC_PLL1DIVR1_DIVQ_Pos);

        /* Включение DIVQ */
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL1QEN_Msk;
    }

    /* DIVS */
    if (config->pll1.divs == 0U || config->pll1.divs > 8U)
    {
        /* Установка значения DIVS по умолчанию */
        RCC->PLL1DIVR2 |= 0x1U;
    }
    else
    {
        /* Установка значения DIVS */
        RCC->PLL1DIVR2 |= ((config->pll1.divs - 1U) << RCC_PLL1DIVR2_DIVS_Pos);

        /* Включение DIVS */
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL1SEN_Msk;
    }

    /* Установка значения и включение дробной части коэффициента умножения для VCO */
    RCC->PLL1FRACR = (config->pll1.fracn << RCC_PLL1FRACR_FRACN_Pos);

    /* Включение дробной части коэффициента умножения для VCO */
    if (config->pll1.fracn != 0U)
    {
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL1FRACEN_Msk;
    }

    /* Небольшая задержка после включения */
    hal_systick_delay(1U);

    /* Установка состояния PLL1 */
    RCC->CR |= config->pll1.enable;

    /* Ожидание готовности PLL1 */
    if (config->pll1.enable == RCC_PLL1_ENABLE)
    {
        while ((RCC->CR & RCC_CR_PLL1RDY_Msk) == 0U);
    }

    /* PLL2 ---------------------------------------------------------------- */

    /* Сброс PLL2DIVR1 и PLL2DIVR2 */
    RCC->PLL2DIVR1 = 0U;
    RCC->PLL2DIVR2 = 0U;

    /* DIVN */
    if (config->pll2.divn < 8U || config->pll2.divn > 420U)
    {
        /* Установка значения DIVN по умолчанию */
        RCC->PLL2DIVR1 |= 0x80U;
    }
    else
    {
        /* Установка значения DIVN */
        RCC->PLL2DIVR1 |= ((config->pll2.divn - 1U) << RCC_PLL2DIVR1_DIVN_Pos);
    }

    /* DIVP */
    if (config->pll2.divp == 0U || config->pll2.divp > 128U)
    {
        /* Установка значения DIVP по умолчанию */
        RCC->PLL2DIVR1 |= 0x200U;
    }
    else
    {
        /* Установка значения DIVP */
        RCC->PLL2DIVR1 |= ((config->pll2.divp - 1U) << RCC_PLL2DIVR1_DIVP_Pos);

        /* Включение DIVP */
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL2PEN_Msk;
    }

    /* DIVQ */
    if (config->pll2.divq == 0U || config->pll2.divq > 128U)
    {
        /* Установка значения DIVQ по умолчанию */
        RCC->PLL2DIVR1 |= 0x10000U;
    }
    else
    {
        /* Установка значения DIVQ */
        RCC->PLL2DIVR1 |= ((config->pll2.divq - 1U) << RCC_PLL2DIVR1_DIVQ_Pos);

        /* Включение DIVQ */
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL2QEN_Msk;
    }

    /* DIVR */
    if (config->pll2.divr == 0U || config->pll2.divr > 128U)
    {
        /* Установка значения DIVR по умолчанию */
        RCC->PLL2DIVR1 |= 0x1000000U;
    }
    else
    {
        /* Установка значения DIVR */
        RCC->PLL2DIVR1 |= ((config->pll2.divr - 1U) << RCC_PLL2DIVR1_DIVR_Pos);

        /* Включение DIVR */
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL2REN_Msk;
    }

    /* DIVS */
    if (config->pll2.divs == 0U || config->pll2.divs > 8U)
    {
        /* Установка значения DIVS по умолчанию */
        RCC->PLL2DIVR2 |= 0x1U;
    }
    else
    {
        /* Установка значения DIVS */
        RCC->PLL2DIVR2 |= ((config->pll2.divs - 1U) << RCC_PLL2DIVR2_DIVS_Pos);

        /* Включение DIVS */
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL2SEN_Msk;
    }

    /* DIVT */
    if (config->pll2.divt == 0U || config->pll2.divt > 8U)
    {
        /* Установка значения DIVT по умолчанию */
        RCC->PLL2DIVR2 |= 0x100U;
    }
    else
    {
        /* Установка значения DIVT */
        RCC->PLL2DIVR2 |= ((config->pll2.divt - 1U) << RCC_PLL2DIVR2_DIVT_Pos);

        /* Включение DIVT */
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL2TEN_Msk;
    }

    /* Установка значения и включение дробной части коэффициента умножения для VCO */
    RCC->PLL2FRACR = (config->pll2.fracn << RCC_PLL2FRACR_FRACN_Pos);

    /* Включение дробной части коэффициента умножения для VCO */
    if (config->pll2.fracn != 0U)
    {
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL2FRACEN_Msk;
    }

    /* Небольшая задержка после включения */
    hal_systick_delay(1U);

    /* Установка состояния PLL2 */
    RCC->CR |= config->pll2.enable;

    /* Ожидание готовности PLL2 */
    if (config->pll2.enable == RCC_PLL2_ENABLE)
    {
        while ((RCC->CR & RCC_CR_PLL2RDY_Msk) == 0U);
    }

    /* PLL3 ---------------------------------------------------------------- */

    /* Сброс PLL3DIVR1 и PLL3DIVR2 */
    RCC->PLL3DIVR1 = 0U;
    RCC->PLL3DIVR2 = 0U;

    /* DIVN */
    if (config->pll3.divn < 8U || config->pll3.divn > 420U)
    {
        /* Установка значения DIVN по умолчанию */
        RCC->PLL3DIVR1 |= 0x80U;
    }
    else
    {
        /* Установка значения DIVN */
        RCC->PLL3DIVR1 |= ((config->pll3.divn - 1U) << RCC_PLL3DIVR1_DIVN_Pos);
    }

    /* DIVP */
    if (config->pll3.divp == 0U || config->pll3.divp > 128U)
    {
        /* Установка значения DIVP по умолчанию */
        RCC->PLL3DIVR1 |= 0x200U;
    }
    else
    {
        /* Установка значения DIVP */
        RCC->PLL3DIVR1 |= ((config->pll3.divp - 1U) << RCC_PLL3DIVR1_DIVP_Pos);

        /* Включение DIVP */
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL3PEN_Msk;
    }

    /* DIVQ */
    if (config->pll3.divq == 0U || config->pll3.divq > 128U)
    {
        /* Установка значения DIVQ по умолчанию */
        RCC->PLL3DIVR1 |= 0x10000U;
    }
    else
    {
        /* Установка значения DIVQ */
        RCC->PLL3DIVR1 |= ((config->pll3.divq - 1U) << RCC_PLL3DIVR1_DIVQ_Pos);

        /* Включение DIVQ */
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL3QEN_Msk;
    }

    /* DIVR */
    if (config->pll3.divr == 0U || config->pll3.divr > 128U)
    {
        /* Установка значения DIVR по умолчанию */
        RCC->PLL3DIVR1 |= 0x1000000U;
    }
    else
    {
        /* Установка значения DIVR */
        RCC->PLL3DIVR1 |= ((config->pll3.divr - 1U) << RCC_PLL3DIVR1_DIVR_Pos);

        /* Включение DIVR */
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL3REN_Msk;
    }

    /* DIVS */
    if (config->pll3.divs == 0U || config->pll3.divs > 8U)
    {
        /* Установка значения DIVS по умолчанию */
        RCC->PLL3DIVR2 |= 0x1U;
    }
    else
    {
        /* Установка значения DIVS */
        RCC->PLL3DIVR2 |= ((config->pll3.divs - 1U) << RCC_PLL3DIVR2_DIVS_Pos);

        /* Включение DIVS */
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL3SEN_Msk;
    }

    /* Установка значения и включение дробной части коэффициента умножения для VCO */
    RCC->PLL3FRACR = (config->pll3.fracn << RCC_PLL3FRACR_FRACN_Pos);

    /* Включение дробной части коэффициента умножения для VCO */
    if (config->pll3.fracn != 0U)
    {
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL3FRACEN_Msk;
    }

    /* Небольшая задержка после включения */
    hal_systick_delay(1U);

    /* Установка состояния PLL3 */
    RCC->CR |= config->pll3.enable;

    /* Ожидание готовности PLL3 */
    if (config->pll3.enable == RCC_PLL3_ENABLE)
    {
        while ((RCC->CR & RCC_CR_PLL3RDY_Msk) == 0U);
    }

    /* BUS ----------------------------------------------------------------- */

    /* Установка значения делителя ядра CPU */
    RCC->CDCFGR = config->cpu_div;

    /* Установка значения делителя шины AHB */
    RCC->BMCFGR = config->ahb_div;

    /* Установка значения делителя шины APB1, APB2, APB4, APB5 */
    RCC->APBCFGR = config->apb1_div |
                   config->apb2_div |
                   config->apb4_div |
                   config->apb5_div;

    /* SYSTEM -------------------------------------------------------------- */

    /* Проверка соответствия системного источника тактирования и состояния HSE/PLL */
    if (config->system_clksource == RCC_SYSTEM_CLKSOURCE_HSI)
    {
        /* HSI по умолчанию включен */
    }
    else if (config->system_clksource == RCC_SYSTEM_CLKSOURCE_HSE)
    {
        assert(config->hse_enable == RCC_HSE_ENABLE);
    }
    else if (config->system_clksource == RCC_SYSTEM_CLKSOURCE_PLL1P)
    {
        assert(config->pll1.enable == RCC_PLL1_ENABLE);
    }
    else
    {
        assert(0);
    }

    /* Настройка системного источника тактирования */
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW_Msk) | config->system_clksource;

    /* Ожидание переключения системного источника тактирования */
    while (((RCC->CFGR & RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos) != config->system_clksource);

    /* Настройка источника тактирования XSPI2 */
    RCC->CCIPR1 = (RCC->CCIPR1 & ~RCC_CCIPR1_XSPI2SEL_Msk) | config->xspi2_clksource;
}
/* ------------------------------------------------------------------------- */

__WEAK void hal_rcc_hserdy_timeout_callback(void)
{

}
/* ------------------------------------------------------------------------- */

__WEAK void hal_rcc_lserdy_timeout_callback(void)
{

}
/* ------------------------------------------------------------------------- */
