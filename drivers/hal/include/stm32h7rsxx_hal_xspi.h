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

#ifndef STM32H7RSXX_HAL_XSPI_H
#define STM32H7RSXX_HAL_XSPI_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "stm32h7rsxx_hal_def.h"

/* Exported macros --------------------------------------------------------- */

/* Включение тактирования XSPI1 */
#define HAL_XSPI1_ENABLE_CLOCK() \
    (RCC->AHB5ENR |= RCC_AHB5ENR_XSPI1EN_Msk)

/* Включение тактирования XSPI2 */
#define HAL_XSPI2_ENABLE_CLOCK() \
    (RCC->AHB5ENR |= RCC_AHB5ENR_XSPI2EN_Msk)

/* Включение защиты тактирования XSPI */
#define HAL_XSPI_ENABLE_CLOCK_PROTECT() \
    (RCC->CKPROTR |= RCC_CKPROTR_XSPICKP_Msk)

/* Exported constants ------------------------------------------------------ */

/* Режим работы XSPI */
#define XSPI_MODE0                          (0x00000000UL)
#define XSPI_MODE3                          (0x00000001UL)

/* Тип внешней памяти, подключенной к XSPI */
#define XSPI_MEMORY_TYPE_MICRON             (0x00000000UL)
#define XSPI_MEMORY_TYPE_MACRONIX           (0x01000000UL)
#define XSPI_MEMORY_TYPE_STANDARD           (0x02000000UL)

/* Размер внешней памяти, подключенной к XSPI */
#define XSPI_MEMORY_SIZE_16B                (0x00000000UL)
#define XSPI_MEMORY_SIZE_32B                (0x00010000UL)
#define XSPI_MEMORY_SIZE_64B                (0x00020000UL)
#define XSPI_MEMORY_SIZE_128B               (0x00030000UL)
#define XSPI_MEMORY_SIZE_256B               (0x00040000UL)
#define XSPI_MEMORY_SIZE_512B               (0x00050000UL)
#define XSPI_MEMORY_SIZE_1KB                (0x00060000UL)
#define XSPI_MEMORY_SIZE_2KB                (0x00070000UL)
#define XSPI_MEMORY_SIZE_4KB                (0x00080000UL)
#define XSPI_MEMORY_SIZE_8KB                (0x00090000UL)
#define XSPI_MEMORY_SIZE_16KB               (0x000A0000UL)
#define XSPI_MEMORY_SIZE_32KB               (0x000B0000UL)
#define XSPI_MEMORY_SIZE_64KB               (0x000C0000UL)
#define XSPI_MEMORY_SIZE_128KB              (0x000D0000UL)
#define XSPI_MEMORY_SIZE_256KB              (0x000E0000UL)
#define XSPI_MEMORY_SIZE_512KB              (0x000F0000UL)
#define XSPI_MEMORY_SIZE_1MB                (0x00100000UL)
#define XSPI_MEMORY_SIZE_2MB                (0x00110000UL)
#define XSPI_MEMORY_SIZE_4MB                (0x00120000UL)
#define XSPI_MEMORY_SIZE_8MB                (0x00130000UL)
#define XSPI_MEMORY_SIZE_16MB               (0x00140000UL)
#define XSPI_MEMORY_SIZE_32MB               (0x00150000UL)
#define XSPI_MEMORY_SIZE_64MB               (0x00160000UL)
#define XSPI_MEMORY_SIZE_128MB              (0x00170000UL)
#define XSPI_MEMORY_SIZE_256MB              (0x00180000UL)
#define XSPI_MEMORY_SIZE_512MB              (0x00190000UL)
#define XSPI_MEMORY_SIZE_1GB                (0x001A0000UL)
#define XSPI_MEMORY_SIZE_2GB                (0x001B0000UL)
#define XSPI_MEMORY_SIZE_4GB                (0x001C0000UL)
#define XSPI_MEMORY_SIZE_8GB                (0x001D0000UL)
#define XSPI_MEMORY_SIZE_16GB               (0x001E0000UL)
#define XSPI_MEMORY_SIZE_32GB               (0x001F0000UL)

/* Функциональный режим работы XSPI */
#define XSPI_INDIRECT_WRITE_MODE            (0x00000000UL)
#define XSPI_INDIRECT_READ_MODE             (0x10000000UL)
#define XSPI_AUTOMATIC_STATUS_POLLING_MODE  (0x20000000UL)
#define XSPI_MEMORY_MAPPED_MODE             (0x30000000UL)

/* Режим фазы инструкции (количество линий) */
#define XSPI_INSTRUCTION_NO                 (0x00000000UL)
#define XSPI_INSTRUCTION_1_LINE             (0x00000001UL)
#define XSPI_INSTRUCTION_2_LINES            (0x00000002UL)
#define XSPI_INSTRUCTION_4_LINES            (0x00000003UL)
#define XSPI_INSTRUCTION_8_LINES            (0x00000004UL)

/* Состояние DTR фазы инструкции */
#define XSPI_INSTRUCTION_DTR_DISABLE        (0x00000000UL)
#define XSPI_INSTRUCTION_DTR_ENABLE         (0x00000008UL)

/* Размер инструкции в битах */
#define XSPI_INSTRUCTION_8BIT               (0x00000000UL)
#define XSPI_INSTRUCTION_16BIT              (0x00000010UL)
#define XSPI_INSTRUCTION_24BIT              (0x00000020UL)
#define XSPI_INSTRUCTION_32BIT              (0x00000030UL)

/* Режим фазы адреса (количество линий) */
#define XSPI_ADDRESS_NO                     (0x00000000UL)
#define XSPI_ADDRESS_1_LINE                 (0x00000100UL)
#define XSPI_ADDRESS_2_LINES                (0x00000200UL)
#define XSPI_ADDRESS_4_LINES                (0x00000300UL)
#define XSPI_ADDRESS_8_LINES                (0x00000400UL)

/* Состояние DTR фазы адреса */
#define XSPI_ADDRESS_DTR_DISABLE            (0x00000000UL)
#define XSPI_ADDRESS_DTR_ENABLE             (0x00000800UL)

/* Размер адреса в битах */
#define XSPI_ADDRESS_8BIT                   (0x00000000UL)
#define XSPI_ADDRESS_16BIT                  (0x00001000UL)
#define XSPI_ADDRESS_24BIT                  (0x00002000UL)
#define XSPI_ADDRESS_32BIT                  (0x00003000UL)

/* Режим фазы альтернативных данных (количество линий) */
#define XSPI_ALTERNATE_BYTE_NO              (0x00000000UL)
#define XSPI_ALTERNATE_BYTE_1_LINE          (0x00010000UL)
#define XSPI_ALTERNATE_BYTE_2_LINES         (0x00020000UL)
#define XSPI_ALTERNATE_BYTE_4_LINES         (0x00030000UL)
#define XSPI_ALTERNATE_BYTE_8_LINES         (0x00040000UL)

/* Состояние DTR фазы альтернативных данных */
#define XSPI_ALTERNATE_BYTE_DTR_DISABLE     (0x00000000UL)
#define XSPI_ALTERNATE_BYTE_DTR_ENABLE      (0x00080000UL)

/* Размер альтернативных данных в битах */
#define XSPI_ALTERNATE_BYTE_8BIT            (0x00000000UL)
#define XSPI_ALTERNATE_BYTE_16BIT           (0x00100000UL)
#define XSPI_ALTERNATE_BYTE_24BIT           (0x00200000UL)
#define XSPI_ALTERNATE_BYTE_32BIT           (0x00300000UL)

/* Режим фазы данных (количество линий) */
#define XSPI_DATA_NO                        (0x00000000UL)
#define XSPI_DATA_1_LINE                    (0x01000000UL)
#define XSPI_DATA_2_LINES                   (0x02000000UL)
#define XSPI_DATA_4_LINES                   (0x03000000UL)
#define XSPI_DATA_8_LINES                   (0x04000000UL)
#define XSPI_DATA_16_LINES                  (0x05000000UL)

/* Состояние DTR фазы данных */
#define XSPI_DATA_DTR_DISABLE               (0x00000000UL)
#define XSPI_DATA_DTR_ENABLE                (0x08000000UL)

/* Состояние DQS */
#define XSPI_DQS_DISABLE                    (0x00000000UL)
#define XSPI_DQS_ENABLE                     (0x20000000UL)

/* Состояние задержки на четверть такта/периода */
#define XSPI_DHQC_DISABLE                   (0x00000000UL)
#define XSPI_DHQC_ENABLE                    (0x10000000UL)

/* Exported types ---------------------------------------------------------- */

/* Структура регистров XSPI */
typedef XSPI_TypeDef xspi_t;


/* Конфигурационная структура XSPI */
typedef struct
{
    uint32_t mode;              /* Режим работы */

    uint32_t prescaler;         /* Делитель часов, диапазон значений: 1-256 */

    uint32_t memory_type;       /* Тип внешней памяти */

    uint32_t memory_size;       /* Размер внешней памяти */

    uint32_t cs_high_time;      /* Длительность сигнала выбора */

    uint32_t fifo_threshold;    /* Порог заполнения буфера FIFO, диапазон значений: 1-32 */
} xspi_config_t;


/* Структура параметров команды XSPI */
typedef struct
{
    uint32_t functional_mode;               /* Функциональный режим */

    uint32_t instruction_mode;              /* Режим фазы инструкции */

    uint32_t instruction_size;              /* Размер инструкции */

    uint32_t instruction_dtr_enable;        /* Состояние DTR фазы инструкции */

    uint32_t instruction;                   /* Код инструкции */

    uint32_t address_mode;                  /* Режим фазы адреса */

    uint32_t address_size;                  /* Размер адреса */

    uint32_t address_dtr_enable;            /* Состояние DTR фазы адреса */

    uint32_t address;                       /* Адресное значение */

    uint32_t alternate_byte_mode;           /* Режим фазы альтернативных данных */

    uint32_t alternate_byte_size;           /* Размер альтернативных данных */

    uint32_t alternate_byte_dtr_enable;     /* Состояние DTR фазы альтернативных данных */

    uint32_t alternate_byte;                /* Альтернативные данные */

    uint32_t data_mode;                     /* Режим фазы данных */

    uint32_t data_size;                     /* Размер данных в байтах */

    uint32_t data_dtr_enable;               /* Состояние DTR фазы данных */

    void * data;                            /* Указатель на буфер данных */

    uint32_t dqs_enable;                    /* Состояние DQS */

    uint32_t dummy_cycles;                  /* Количество фиктивных тактов, диапазон значений: 0-31 */

    uint32_t dhqc_enable;                   /* Состояние задержки на четверть такта/периода */
} xspi_command_t;


/* Структура обработчика XSPI */
typedef struct
{
    xspi_t * instance;      /* Указатель на структуру XSPI */
} xspi_handle_t;

/* Exported variables ------------------------------------------------------ */

/* Exported function prototypes -------------------------------------------- */

void hal_xspi_init(xspi_handle_t * handle, const xspi_config_t * config);

hal_status_t hal_xspi_execute_command(xspi_handle_t * handle, const xspi_command_t * command, uint32_t timeout);

hal_status_t hal_xspi_setup_memory_mapped_mode(xspi_handle_t * handle, const xspi_command_t * command, uint32_t timeout);

/* Exported callback function prototypes ----------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7RSXX_HAL_XSPI_H */
