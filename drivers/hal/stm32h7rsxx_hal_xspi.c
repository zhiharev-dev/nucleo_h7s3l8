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

#include "stm32h7rsxx_hal_xspi.h"
#include "stm32h7rsxx_hal_systick.h"

/* Private macros ---------------------------------------------------------- */

/* Проверка диапазона */
#define HAL_XSPI_IS_IN_RANGE(value, min, max) \
    (((value) >= (min)) && ((value) <= (max)))

/* Значение CSHT регистра DCR1 (с проверкой диапазона) */
#define HAL_XSPI_DCR1_CSHT(value) \
    ((HAL_XSPI_IS_IN_RANGE(value, 1U, 64U)) ? \
     ((value - 1U) << XSPI_DCR1_CSHT_Pos) : 0U)

/* Значение PRESCALER регистра DCR2 (с проверкой диапазона) */
#define HAL_XSPI_DCR2_PRESCALER(div) \
    ((HAL_XSPI_IS_IN_RANGE(div, 1U, 256U)) ? \
     ((div - 1U) << XSPI_DCR2_PRESCALER_Pos) : 0U)

/* Значение FTHRES регистра CR (с проверкой диапазона) */
#define HAL_XSPI_CR_FTHRES(value) \
    ((HAL_XSPI_IS_IN_RANGE(value, 1U, 32U)) ? \
     ((value - 1U) << XSPI_CR_FTHRES_Pos) : 0U)

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/*
 * Инициализация XSPI
 *
 * Параметры:
 *     handle - указатель на структуру обработчика XSPI
 *     config - указатель на конфигурационную структуру XSPI
 */
void hal_xspi_init(xspi_handle_t * handle, const xspi_config_t * config)
{
    /* Проверка входных параметров */
    assert(handle != NULL);
    assert(handle->instance != NULL);
    assert(config != NULL);

    /* Получение указателя на структуру XSPI */
    xspi_t * instance = handle->instance;

    /* Выключение XSPI, перед настройкой */
    instance->CR &= ~XSPI_CR_EN_Msk;

    /* Настройка параметров XSPI регистра DCR1 */
    instance->DCR1 = config->mode        |
                     config->memory_type |
                     config->memory_size |
                     HAL_XSPI_DCR1_CSHT(config->cs_high_time);

    /* Настройка параметров XSPI регистра DCR2 */
    instance->DCR2 = HAL_XSPI_DCR2_PRESCALER(config->prescaler);

    /* Настройка параметров и включение XSPI */
    instance->CR = HAL_XSPI_CR_FTHRES(config->fifo_threshold) |
                   XSPI_CR_EN_Msk;
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
hal_status_t hal_xspi_execute_command(xspi_handle_t * handle, const xspi_command_t * command, uint32_t timeout)
{
    /* Проверка входных параметров */
    assert(handle != NULL);
    assert(handle->instance != NULL);
    assert(command != NULL);

    /* Получение указателя на структуру XSPI */
    xspi_t * instance = handle->instance;

    /* Размер передаваемых/принимаемых данных */
    size_t data_size = command->data_size;

    /* Указатель на буфер данных */
    uint8_t * data = (uint8_t *) command->data;

    /* Указатель на регистр данных XSPI */
    volatile uint8_t * xspi_data = (volatile uint8_t *) &instance->DR;

    /* Сохранение начального значения системного таймера */
    uint32_t tick_start = hal_systick_get_ticks();

    /* Ожидание завершения предыдущей операции */
    while ((instance->SR & XSPI_SR_BUSY_Msk) != 0U)
    {
        if (hal_systick_get_ticks() - tick_start > timeout)
        {
            return HAL_BUSY;
        }
    }

    /* Настройка функционального режима (с сохранением остальных битов CR) */
    instance->CR = (instance->CR & ~XSPI_CR_FMODE_Msk) | command->functional_mode;

    /* Настройка длины данных, если фаза данных присутствует */
    if (command->data_mode != XSPI_DATA_NO && command->data_size > 0U)
    {
        instance->DLR = data_size - 1U;
    }

    /* Настройка количества фиктивных циклов */
    instance->TCR = command->dummy_cycles | command->dhqc_enable;

    /* Настройка регистра команд/конфигурации (CCR) */
    instance->CCR = command->instruction_mode          |
                    command->instruction_size          |
                    command->instruction_dtr_enable    |
                    command->address_mode              |
                    command->address_size              |
                    command->address_dtr_enable        |
                    command->alternate_byte_mode       |
                    command->alternate_byte_size       |
                    command->alternate_byte_dtr_enable |
                    command->data_mode                 |
                    command->data_dtr_enable           |
                    command->dqs_enable;

    /* Запись инструкции (если требуется) */
    if (command->instruction_mode != XSPI_INSTRUCTION_NO)
    {
        instance->IR = command->instruction;
    }

    /* Запись альтернативных данных (если требуется) */
    if (command->alternate_byte_mode != XSPI_ALTERNATE_BYTE_NO)
    {
        instance->ABR = command->alternate_byte;
    }

    /* Запись адреса (если требуется) */
    if (command->address_mode != XSPI_ADDRESS_NO)
    {
        instance->AR = command->address;
    }

    /* Режим косвенной записи */
    if (command->functional_mode == XSPI_INDIRECT_WRITE_MODE)
    {
        /* Передача данных в FIFO */
        while (data_size > 0U)
        {
            /* Ожидание освобождения места в FIFO */
            while ((instance->SR & XSPI_SR_FTF_Msk) == 0U)
            {
                if (hal_systick_get_ticks() - tick_start > timeout)
                {
                    return HAL_TIMEOUT;
                }
            }

            /* Запись байта данных */
            *xspi_data = *data;

            /* Продвижение указателя и уменьшение счетчика */
            data++;
            data_size--;
        }

        /* Ожидание завершения передачи */
        while ((instance->SR & XSPI_SR_TCF_Msk) == 0U)
        {
            if (hal_systick_get_ticks() - tick_start > timeout)
            {
                return HAL_TIMEOUT;
            }
        }

        /* Сброс флага завершения передачи */
        instance->FCR = XSPI_FCR_CTCF_Msk;
    }

    /* Режим косвенного чтения */
    if (command->functional_mode == XSPI_INDIRECT_READ_MODE)
    {
        /* Прием данных из FIFO */
        while (data_size > 0U)
        {
            /* Ожидание поступления данных в FIFO */
            while ((instance->SR & (XSPI_SR_FTF_Msk | XSPI_SR_TCF_Msk)) == 0U)
            {
                if (hal_systick_get_ticks() - tick_start > timeout)
                {
                    return HAL_TIMEOUT;
                }
            }

            /* Чтение байта данных */
            *data = *xspi_data;

            /* Продвижение указателя и уменьшение счетчика */
            data++;
            data_size--;
        }

        /* Ожидание завершения передачи */
        while ((instance->SR & XSPI_SR_TCF_Msk) == 0U)
        {
            if (hal_systick_get_ticks() - tick_start > timeout)
            {
                return HAL_TIMEOUT;
            }
        }

        /* Сброс флага завершения передачи */
        instance->FCR = XSPI_FCR_CTCF_Msk;
    }

    return HAL_OK;
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
hal_status_t hal_xspi_setup_memory_mapped_mode(xspi_handle_t * handle, const xspi_command_t * command, uint32_t timeout)
{
    /* Проверка входных параметров */
    assert(handle != NULL);
    assert(handle->instance != NULL);
    assert(command != NULL);

    /* Получение указателя на структуру XSPI */
    xspi_t * instance = handle->instance;

    /* Сохранение начального значения системного таймера */
    uint32_t tick_start = hal_systick_get_ticks();

    /* Ожидание завершения предыдущей операции */
    while ((instance->SR & XSPI_SR_BUSY_Msk) != 0U)
    {
        if (hal_systick_get_ticks() - tick_start > timeout)
        {
            return HAL_BUSY;
        }
    }

    /* Сброс функционального режима */
    instance->CR &= ~XSPI_CR_FMODE_Msk;

    /* Настройка количества фиктивных циклов */
    instance->TCR = command->dummy_cycles | command->dhqc_enable;

    /* Настройка регистра команд/конфигурации (CCR) */
    instance->CCR = command->instruction_mode          |
                    command->instruction_size          |
                    command->instruction_dtr_enable    |
                    command->address_mode              |
                    command->address_size              |
                    command->address_dtr_enable        |
                    command->alternate_byte_mode       |
                    command->alternate_byte_size       |
                    command->alternate_byte_dtr_enable |
                    command->data_mode                 |
                    command->data_dtr_enable           |
                    command->dqs_enable;

    /* Запись инструкции (если требуется) */
    if (command->instruction_mode != XSPI_INSTRUCTION_NO)
    {
        instance->IR = command->instruction;
    }

    /* Запись альтернативных данных (если требуется) */
    if (command->alternate_byte_mode != XSPI_ALTERNATE_BYTE_NO)
    {
        instance->ABR = command->alternate_byte;
    }

    /* Ожидание завершения настройки */
    while ((instance->SR & XSPI_SR_BUSY_Msk) != 0U)
    {
        if (hal_systick_get_ticks() - tick_start > timeout)
        {
            return HAL_BUSY;
        }
    }

    /* Переключение в режим отображения в память */
    instance->CR |= XSPI_MEMORY_MAPPED_MODE;

    return HAL_OK;
}
/* ------------------------------------------------------------------------- */
