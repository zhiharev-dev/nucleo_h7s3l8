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

#include "mx25uw.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

#define MX25UW_XSPI_TIMEOUT     (5000U)

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

mx25uw_t mx25uw =
{
    .xspi = &xspi2,
};

/* Private function prototypes --------------------------------------------- */

static bool mx25uw_is_valid(void);

static hal_status_t mx25uw_enable_opi_dtr_mode(void);

static hal_status_t mx25uw_read_id(uint8_t id[]);

static hal_status_t mx25uw_read_status_reg(uint8_t * status_reg);

static bool mx25uw_is_write_enable(void);

static hal_status_t mx25uw_write_enable(void);

static hal_status_t mx25uw_write_cfg_reg2(uint32_t address, uint8_t value);

static hal_status_t mx25uw_set_opi_dtr_bit(void);

/* Private user code ------------------------------------------------------- */

/*
 * Инициализация MX25UW в режиме OPI DTR
 *
 * Возвращает: статус выполнения операции
 */
hal_status_t mx25uw_init(void)
{
    if (mx25uw_is_valid() != true)
    {
        return HAL_ERROR;
    }
    else if (mx25uw_enable_opi_dtr_mode() != HAL_OK)
    {
        return HAL_ERROR;
    }
    else
    {
        return HAL_OK;
    }
}
/* ------------------------------------------------------------------------- */

/*
 * Установка Memory Mapped Mode для MX25UW в режиме OPI DTR
 *
 * Возвращает: статус выполнения операции
 */
hal_status_t mx25uw_enter_memory_mapped_mode(void)
{
    xspi_command_t xspi_command =
    {
        .instruction_mode = XSPI_INSTRUCTION_8_LINES,
        .instruction_dtr_enable = XSPI_INSTRUCTION_DTR_ENABLE,
        .instruction_size = XSPI_INSTRUCTION_16BIT,
        .instruction = MX25UW_OPI_READ_DTR_CMD,
        .address_mode = XSPI_ADDRESS_8_LINES,
        .address_dtr_enable = XSPI_ADDRESS_DTR_ENABLE,
        .address_size = XSPI_ADDRESS_32BIT,
        .data_mode = XSPI_DATA_8_LINES,
        .data_dtr_enable = XSPI_DATA_DTR_ENABLE,
        .dqs_enable = XSPI_DQS_ENABLE,
        .dummy_cycles = 20,
        .dhqc_enable = XSPI_DHQC_ENABLE,
    };

    /* Выполнение команды */
    return xspi_setup_memory_mapped_mode(mx25uw.xspi, &xspi_command, MX25UW_XSPI_TIMEOUT);
}
/* ------------------------------------------------------------------------- */

/* Проверка идентификатора MX25UW */
static bool mx25uw_is_valid(void)
{
    uint8_t id[3] = {0};

    if (mx25uw_read_id(id) != HAL_OK)
    {
        return false;
    }
    else if (id[0] != MX25UW_MFR_ID)
    {
        return false;
    }
    else
    {
        return true;
    }
}
/* ------------------------------------------------------------------------- */

/* Переключение MX25UW в режим OPI DTR */
static hal_status_t mx25uw_enable_opi_dtr_mode(void)
{
    if (mx25uw_write_enable() != HAL_OK)
    {
        return HAL_ERROR;
    }
    else if (mx25uw_is_write_enable() != true)
    {
        return HAL_ERROR;
    }
    else if (mx25uw_set_opi_dtr_bit() != HAL_OK)
    {
        return HAL_ERROR;
    }
    else
    {
        return HAL_OK;
    }
}
/* ------------------------------------------------------------------------- */

/*
 * Чтение идентификатора
 *
 * Параметры: id - указатель на место записи данных идентификатора (3 байта)
 *
 * Возвращает: статус выполнения операции
 */
static hal_status_t mx25uw_read_id(uint8_t id[])
{
    /* Проверка входных параметров */
    assert(id != NULL);

    xspi_command_t xspi_command =
    {
        .functional_mode = XSPI_INDIRECT_READ_MODE,
        .instruction_mode = XSPI_INSTRUCTION_1_LINE,
        .instruction_size = XSPI_INSTRUCTION_8BIT,
        .instruction = MX25UW_READ_ID_CMD,
        .data_mode = XSPI_DATA_1_LINE,
        .data_size = 3,
        .data = (void *) id,
    };

    /* Выполнение команды */
    return xspi_execute_command(mx25uw.xspi, &xspi_command, MX25UW_XSPI_TIMEOUT);
}
/* ------------------------------------------------------------------------- */

/*
 * Чтение значения регистра статуса
 *
 * Параметры: status_reg - указатель на место записи значения регистра статусов
 *
 * Возвращает: статус выполнения операции
 */
static hal_status_t mx25uw_read_status_reg(uint8_t * status_reg)
{
    /* Проверка входных параметров */
    assert(status_reg != NULL);

    xspi_command_t xspi_command =
    {
        .functional_mode = XSPI_INDIRECT_READ_MODE,
        .instruction_mode = XSPI_INSTRUCTION_1_LINE,
        .instruction_size = XSPI_INSTRUCTION_8BIT,
        .instruction = MX25UW_READ_STATUS_REG_CMD,
        .data_mode = XSPI_DATA_1_LINE,
        .data_size = 1,
        .data = (void *) status_reg,
    };

    /* Выполнение команды */
    return xspi_execute_command(mx25uw.xspi, &xspi_command, MX25UW_XSPI_TIMEOUT);
}
/* ------------------------------------------------------------------------- */

/* Проверка состояния разрешения на запись */
static bool mx25uw_is_write_enable(void)
{
    uint8_t SR;

    if (mx25uw_read_status_reg(&SR) != HAL_OK)
    {
        return false;
    }
    else if ((SR & 0x02) == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
/* ------------------------------------------------------------------------- */

/* Установка разрешения на запись */
static hal_status_t mx25uw_write_enable(void)
{
    xspi_command_t xspi_command =
    {
        .functional_mode = XSPI_INDIRECT_WRITE_MODE,
        .instruction_mode = XSPI_INSTRUCTION_1_LINE,
        .instruction_size = XSPI_INSTRUCTION_8BIT,
        .instruction = MX25UW_WRITE_ENABLE_CMD,
    };

    /* Выполнение команды */
    return xspi_execute_command(mx25uw.xspi, &xspi_command, MX25UW_XSPI_TIMEOUT);
}
/* ------------------------------------------------------------------------- */

/*
 * Запись значения в конфигурационный регистр
 *
 * Параметры:
 *     address - адрес
 *     value - значение
 *
 * Возвращает: статус выполнения операции
 */
static hal_status_t mx25uw_write_cfg_reg2(uint32_t address, uint8_t value)
{
    xspi_command_t xspi_command =
    {
        .functional_mode = XSPI_INDIRECT_WRITE_MODE,
        .instruction_mode = XSPI_INSTRUCTION_1_LINE,
        .instruction_size = XSPI_INSTRUCTION_8BIT,
        .instruction = MX25UW_WRITE_CFG_REG2_CMD,
        .address_mode = XSPI_ADDRESS_1_LINE,
        .address_size = XSPI_ADDRESS_32BIT,
        .address = address,
        .data_mode = XSPI_DATA_1_LINE,
        .data_size = 1,
        .data = (void *) &value,
    };

    /* Выполнение команды */
    return xspi_execute_command(mx25uw.xspi, &xspi_command, MX25UW_XSPI_TIMEOUT);
}
/* ------------------------------------------------------------------------- */

/* Установка бита OPI DTR в конфигурационном регистре */
static hal_status_t mx25uw_set_opi_dtr_bit(void)
{
    return mx25uw_write_cfg_reg2(0x00000000, 0x02);
}
/* ------------------------------------------------------------------------- */
