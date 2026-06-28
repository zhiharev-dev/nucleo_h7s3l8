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

#ifndef STM32H7RSXX_HAL_MPU_H
#define STM32H7RSXX_HAL_MPU_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "stm32h7rsxx_hal_def.h"

/* Exported macros --------------------------------------------------------- */

/* Exported constants ------------------------------------------------------ */

/* Управление режимом HFNMI и доступом привилегированного режима MPU */
#define MPU_HFNMI_PRIVDEF_NONE      (0x00000000UL)
#define MPU_HARDFAULT_NMI           (0x00000002UL)
#define MPU_PRIVILEGED_DEFAULT      (0x00000004UL)
#define MPU_HFNMI_PRIVDEF           (0x00000006UL)

/* Состояние области MPU */
#define MPU_REGION_DISABLE          (0x00000000UL)
#define MPU_REGION_ENABLE           (0x00000001UL)

/* Номер области MPU */
#define MPU_REGION_NUMBER0          (0x00000000UL)
#define MPU_REGION_NUMBER1          (0x00000001UL)
#define MPU_REGION_NUMBER2          (0x00000002UL)
#define MPU_REGION_NUMBER3          (0x00000003UL)
#define MPU_REGION_NUMBER4          (0x00000004UL)
#define MPU_REGION_NUMBER5          (0x00000005UL)
#define MPU_REGION_NUMBER6          (0x00000006UL)
#define MPU_REGION_NUMBER7          (0x00000007UL)
#define MPU_REGION_NUMBER8          (0x00000008UL)
#define MPU_REGION_NUMBER9          (0x00000009UL)
#define MPU_REGION_NUMBER10         (0x0000000AUL)
#define MPU_REGION_NUMBER11         (0x0000000BUL)
#define MPU_REGION_NUMBER12         (0x0000000CUL)
#define MPU_REGION_NUMBER13         (0x0000000DUL)
#define MPU_REGION_NUMBER14         (0x0000000EUL)
#define MPU_REGION_NUMBER15         (0x0000000FUL)

/* Размер области MPU */
#define MPU_REGION_SIZE_32B         (0x00000008UL)
#define MPU_REGION_SIZE_64B         (0x0000000AUL)
#define MPU_REGION_SIZE_128B        (0x0000000CUL)
#define MPU_REGION_SIZE_256B        (0x0000000EUL)
#define MPU_REGION_SIZE_512B        (0x00000010UL)
#define MPU_REGION_SIZE_1KB         (0x00000012UL)
#define MPU_REGION_SIZE_2KB         (0x00000014UL)
#define MPU_REGION_SIZE_4KB         (0x00000016UL)
#define MPU_REGION_SIZE_8KB         (0x00000018UL)
#define MPU_REGION_SIZE_16KB        (0x0000001AUL)
#define MPU_REGION_SIZE_32KB        (0x0000001CUL)
#define MPU_REGION_SIZE_64KB        (0x0000001EUL)
#define MPU_REGION_SIZE_128KB       (0x00000020UL)
#define MPU_REGION_SIZE_256KB       (0x00000022UL)
#define MPU_REGION_SIZE_512KB       (0x00000024UL)
#define MPU_REGION_SIZE_1MB         (0x00000026UL)
#define MPU_REGION_SIZE_2MB         (0x00000028UL)
#define MPU_REGION_SIZE_4MB         (0x0000002AUL)
#define MPU_REGION_SIZE_8MB         (0x0000002CUL)
#define MPU_REGION_SIZE_16MB        (0x0000002EUL)
#define MPU_REGION_SIZE_32MB        (0x00000030UL)
#define MPU_REGION_SIZE_64MB        (0x00000032UL)
#define MPU_REGION_SIZE_128MB       (0x00000034UL)
#define MPU_REGION_SIZE_256MB       (0x00000036UL)
#define MPU_REGION_SIZE_512MB       (0x00000038UL)
#define MPU_REGION_SIZE_1GB         (0x0000003AUL)
#define MPU_REGION_SIZE_2GB         (0x0000003CUL)
#define MPU_REGION_SIZE_4GB         (0x0000003EUL)

/* Уровень типа расширения области MPU */
#define MPU_TEX_LEVEL0              (0x00000000UL)
#define MPU_TEX_LEVEL1              (0x00080000UL)
#define MPU_TEX_LEVEL2              (0x00100000UL)

/* Права доступа для области MPU */
#define MPU_REGION_NO_ACCESS        (0x00000000UL)
#define MPU_REGION_PRIV_RW          (0x01000000UL)
#define MPU_REGION_PRIV_RW_URO      (0x02000000UL)
#define MPU_REGION_FULL_ACCESS      (0x03000000UL)
#define MPU_REGION_PRIV_RO          (0x04000000UL)
#define MPU_REGION_PRIV_RO_URO      (0x05000000UL)

/* Состояние исполнения */
#define MPU_REGION_EXECUTE_DISABLE  (0x10000000UL)
#define MPU_REGION_EXECUTE_ENABLE   (0x00000000UL)

/* Состояние разделяемости */
#define MPU_REGION_SHAREABLE        (0x00040000UL)
#define MPU_REGION_NOT_SHAREABLE    (0x00000000UL)

/* Состояние кэшируемости */
#define MPU_REGION_CACHEABLE        (0x00020000UL)
#define MPU_REGION_NOT_CACHEABLE    (0x00000000UL)

/* Состояние буферизуемости */
#define MPU_REGION_BUFFERABLE       (0x00010000UL)
#define MPU_REGION_NOT_BUFFERABLE   (0x00000000UL)

/* Exported types ---------------------------------------------------------- */

/* Структура регистров MPU */
typedef MPU_Type mpu_t;


/* Конфигурационная структура области MPU */
typedef struct
{
    uint32_t enable;                    /* Состояние */

    uint32_t number;                    /* Номер */

    uint32_t base_address;              /* Адрес */

    uint32_t size;                      /* Размер */

    uint32_t subregion_disable;         /* Состояние подобластей (битовая маска)(диапазон: 0x00-0xFF) */

    uint32_t type_extension_level;      /* Уровень типа расширения */

    uint32_t access_permission;         /* Права доступа */

    uint32_t execute_enable;            /* Состояние исполнения */

    uint32_t is_shareable;              /* Состояние разделяемости */

    uint32_t is_cacheable;              /* Состояние кэшируемости */

    uint32_t is_bufferable;             /* Состояние буферизуемости */
} mpu_region_config_t;

/* Exported variables ------------------------------------------------------ */

/* Exported function prototypes -------------------------------------------- */

void hal_mpu_region_init(const mpu_region_config_t * config);

void hal_mpu_enable(uint32_t mpu_control);

void hal_mpu_disable(void);

/* Exported callback function prototypes ----------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7RSXX_HAL_MPU_H */
