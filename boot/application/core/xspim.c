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

#include "xspim.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/* Инициализация XSPIM */
void xspim_init(void)
{
    xspim_config_t xspim_config =
    {
        .mux_enable = XSPIM_MUX_DISABLE,
        .override_ncs_enable = XSPIM_OVR_NCS_ENABLE,
        .override_ncs_xspi1 = XSPIM_OVR_NCS2_XSPI1,
        .override_ncs_xspi2 = XSPIM_OVR_NCS1_XSPI2,
    };

    HAL_XSPIM_ENABLE_CLOCK();

    hal_xspim_init(&xspim_config);
}
/* ------------------------------------------------------------------------- */
