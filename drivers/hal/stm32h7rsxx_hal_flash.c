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

#include "stm32h7rsxx_hal_flash.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Значения OPTKEYR для разблокировки OPTCR */
#define FLASH_OPTKEYR1  (0x08192A3BUL)
#define FLASH_OPTKEYR2  (0x4C5D6E7FUL)

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/*
 * Инициализация FLASH
 *
 * Параметры: config - указатель на конфигурационную структуру FLASH
 */
void hal_flash_init(const flash_config_t * config)
{
    /* Проверка входных параметров */
    assert(config != NULL);

    /* Ожидание готовности FLASH */
    while ((FLASH->SR & FLASH_SR_BUSY_Msk) != 0U);

    /* Настройка параметров доступа к FLASH */
    FLASH->ACR = config->latency | config->wrhighfreq;

    /* Синхронизация данных и инструкций */
    __DSB();
    __ISB();
}
/* ------------------------------------------------------------------------- */

/*
 * Инициализация опций FLASH
 *
 * Параметры: config - указатель на конфигурационную структуру опций FLASH
 */
void hal_flash_opt_init(const flash_opt_config_t * config)
{
    /* Проверка входных параметров */
    assert(config != NULL);

    /* Статус сброса устройства (после перезаписи параметров) */
    bool is_reset = false;

    /* OBW1 ---------------------------------------------------------------- */

    /* Ожидание готовности FLASH */
    while ((FLASH->SR & FLASH_SR_BUSY_Msk) != 0U);

    /* Проверка соответствия параметров OBW1 */
    uint32_t FLASH_OBW1SR_Msk = FLASH_OBW1SR_XSPI2_HSLV_Msk;

    uint32_t FLASH_OBW1 = config->xspi2_hslv_enable;

    /* Перезапись параметров OBW1 */
    if ((FLASH->OBW1SR & FLASH_OBW1SR_Msk) != FLASH_OBW1)
    {
        /* Снятие блокировки OPTCR */
        FLASH->OPTKEYR = FLASH_OPTKEYR1;
        FLASH->OPTKEYR = FLASH_OPTKEYR2;

        /* Ожидание снятия блокировки OPTCR */
        while ((FLASH->OPTCR & FLASH_OPTCR_OPTLOCK_Msk) != 0U);

        /* Включение записи опций */
        FLASH->OPTCR |= FLASH_OPTCR_PG_OPT_Msk;

        /* Изменение параметров OBW1 */
        FLASH->OBW1SRP = (FLASH->OBW1SRP & ~FLASH_OBW1SR_Msk) | FLASH_OBW1;

        /* Ожидание завершения записи */
        while ((FLASH->SR & FLASH_SR_QW_Msk) != 0U);

        /* Выключение записи опций */
        FLASH->OPTCR &= ~FLASH_OPTCR_PG_OPT_Msk;

        /* Блокировка OPTCR */
        FLASH->OPTCR |= FLASH_OPTCR_OPTLOCK_Msk;

        /* Сброс устройства */
        is_reset = true;
    }

    /* OBW2 ---------------------------------------------------------------- */

    /* Ожидание готовности FLASH */
    while ((FLASH->SR & FLASH_SR_BUSY_Msk) != 0U);

    /* Проверка соответствия параметров OBW2 */
    uint32_t FLASH_OBW2SR_Msk = FLASH_OBW2SR_ITCM_AXI_SHARE_Msk |
                                FLASH_OBW2SR_DTCM_AXI_SHARE_Msk |
                                FLASH_OBW2SR_ECC_ON_SRAM_Msk;

    uint32_t FLASH_OBW2 = config->itcm_axi_share |
                          config->dtcm_axi_share |
                          config->ecc_on_sram;

    if ((FLASH->OBW2SR & FLASH_OBW2SR_Msk) != FLASH_OBW2)
    {
        /* Снятие блокировки OPTCR */
        FLASH->OPTKEYR = FLASH_OPTKEYR1;
        FLASH->OPTKEYR = FLASH_OPTKEYR2;

        /* Ожидание снятия блокировки OPTCR */
        while ((FLASH->OPTCR & FLASH_OPTCR_OPTLOCK_Msk) != 0U);

        /* Включение записи опций */
        FLASH->OPTCR |= FLASH_OPTCR_PG_OPT_Msk;

        /* Изменение параметров OBW2 */
        FLASH->OBW2SRP = (FLASH->OBW2SRP & ~FLASH_OBW2SR_Msk) | FLASH_OBW2;

        /* Ожидание завершения записи */
        while ((FLASH->SR & FLASH_SR_QW_Msk) != 0U);

        /* Выключение записи опций */
        FLASH->OPTCR &= ~FLASH_OPTCR_PG_OPT_Msk;

        /* Блокировка OPTCR */
        FLASH->OPTCR |= FLASH_OPTCR_OPTLOCK_Msk;

        /* Сброс устройства */
        is_reset = true;
    }

    /* --------------------------------------------------------------------- */

    /* Сброс устройства после перезаписи параметров */
    if (is_reset)
    {
        NVIC_SystemReset();
    }
}
/* ------------------------------------------------------------------------- */
