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

#ifndef XSPI_H
#define XSPI_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "stm32h7rsxx_hal_xspi.h"

/* Exported macros --------------------------------------------------------- */

/* Exported constants ------------------------------------------------------ */

/* Exported types ---------------------------------------------------------- */

/* Exported variables ------------------------------------------------------ */

extern xspi_handle_t xspi2;

/* Exported function prototypes -------------------------------------------- */

void xspi_init(void);

void xspi_setup_max_frequency(void);

hal_status_t xspi_execute_command(xspi_handle_t * handle, const xspi_command_t * command, uint32_t timeout);

hal_status_t xspi_setup_memory_mapped_mode(xspi_handle_t * handle, const xspi_command_t * command, uint32_t timeout);

/* Exported callback function prototypes ----------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XSPI_H */
