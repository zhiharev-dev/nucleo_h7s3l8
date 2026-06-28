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

#include "flash.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/* Инициализация FLASH */
void flash_init(void)
{
    flash_config_t flash_config =
    {
        .latency = FLASH_LATENCY_7WS,
        .wrhighfreq = FLASH_WRHIGHFREQ3,
    };

    flash_opt_config_t flash_opt_config =
    {
        .itcm_axi_share = FLASH_ITCM_AXI_SHARE_128K,
        .dtcm_axi_share = FLASH_DTCM_AXI_SHARE_128K,
        .ecc_on_sram = FLASH_ECC_ON_SRAM_DISABLE,
        .xspi2_hslv_enable = FLASH_XSPI2_HSLV_ENABLE,
    };

    hal_flash_init(&flash_config);
    hal_flash_opt_init(&flash_opt_config);
}
/* ------------------------------------------------------------------------- */
