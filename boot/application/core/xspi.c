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

#include "xspi.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

xspi_handle_t xspi2 =
{
    .instance = XSPI2,
};

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/* Инициализация XSPI */
void xspi_init(void)
{
    xspi_config_t xspi_config =
    {
        .mode = XSPI_MODE0,
        .prescaler = 4,
        .memory_type = XSPI_MEMORY_TYPE_MACRONIX,
        .memory_size = XSPI_MEMORY_SIZE_32MB,
        .cs_high_time = 2,
        .fifo_threshold = 1,
    };

    HAL_XSPI2_ENABLE_CLOCK();

    HAL_XSPI_ENABLE_CLOCK_PROTECT();

    hal_xspi_init(&xspi2, &xspi_config);
}
/* ------------------------------------------------------------------------- */

/* Настройка максимальной скорости работы XSPI */
void xspi_setup_max_frequency(void)
{
    xspi_config_t xspi_config =
    {
        .mode = XSPI_MODE0,
        .prescaler = 1,
        .memory_type = XSPI_MEMORY_TYPE_MACRONIX,
        .memory_size = XSPI_MEMORY_SIZE_32MB,
        .cs_high_time = 2,
        .fifo_threshold = 1,
    };

    hal_xspi_init(&xspi2, &xspi_config);
}
/* ------------------------------------------------------------------------- */

/*
 * Выполнение команды XSPI
 *
 * Параметры:
 *     handle - указатель на структуру обработчика XSPI
 *     command - указатель на структуру параметров команды XSPI
 *     timeout - таймаут ожидания (мc)
 *
 * Возвращает: статус выполнения операции
 */
hal_status_t xspi_execute_command(xspi_handle_t * handle, const xspi_command_t * command, uint32_t timeout)
{
    return hal_xspi_execute_command(handle, command, timeout);
}
/* ------------------------------------------------------------------------- */

/*
 * Настройка режима отображения в память
 *
 * Параметры:
 *     handle - указатель на структуру обработчика XSPI
 *     command - указатель на структуру параметров команды XSPI
 *     timeout - таймаут ожидания (мc)
 *
 * Возвращает: статус выполнения операции
 */
hal_status_t xspi_setup_memory_mapped_mode(xspi_handle_t * handle, const xspi_command_t * command, uint32_t timeout)
{
    return hal_xspi_setup_memory_mapped_mode(handle, command, timeout);
}
/* ------------------------------------------------------------------------- */
