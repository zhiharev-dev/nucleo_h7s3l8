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

#include "main.h"
#include "systick.h"
#include "pwr.h"
#include "flash.h"
#include "rcc.h"
#include "gpio.h"
#include "sbs.h"
#include "xspim.h"
#include "xspi.h"
#include "mx25uw.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

#define VTOR_ADDRESS    (0x08000000UL)

#define HSI_CLOCK       (64000000UL)

#define APP_ADDRESS     (0x70000000UL)

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

static void system_init(void);

static void setup_vector_table(void);

static void setup_fpu(void);

static void setup_mpu(void);

static void setup_cahce(void);

static void app_main(void);

static void jump_app(void);

/* Private user code ------------------------------------------------------- */

int main(void)
{
    system_init();
    app_main();
}
/* ------------------------------------------------------------------------- */

void error(void)
{
    /* Отключение всех прерываний */
    __disable_irq();

    /* Бесконечный цикл остановки системы */
    while (true) {}
}
/* ------------------------------------------------------------------------- */

static void app_main(void)
{
    if (mx25uw_init() != HAL_OK)
    {
        error();
    }

    xspi_setup_max_frequency();

    if (mx25uw_enter_memory_mapped_mode() != HAL_OK)
    {
        error();
    }
    else
    {
        jump_app();
    }
}
/* ------------------------------------------------------------------------- */

static void system_init(void)
{
    setup_vector_table();
    setup_fpu();
    setup_mpu();
    setup_cahce();

    systick_init(HSI_CLOCK);
    pwr_init();
    flash_init();
    rcc_init();
    systick_init(RCC_SYSTEM_CLOCK);
    gpio_init();
    sbs_init();
    xspim_init();
    xspi_init();
}
/* ------------------------------------------------------------------------- */

static void setup_vector_table(void)
{
    /* Запрет всех прерываний на время перенастройки */
    __disable_irq();

    /* Установка нового адреса таблицы векторов */
    SCB->VTOR = VTOR_ADDRESS;

    /* Синхронизация данных и инструкций */
    __DSB();
    __ISB();

    /* Включение прерываний */
    __enable_irq();
}
/* ------------------------------------------------------------------------- */

static void setup_fpu(void)
{
    /* Включение доступа к сопроцессорам FPU */
    SCB->CPACR |= HAL_BIT_SHIFT(0x3, 20) | HAL_BIT_SHIFT(0x3, 22);

    /* Синхронизация данных и инструкций */
    __DSB();
    __ISB();
}
/* ------------------------------------------------------------------------- */

/* Настройка модуля защиты памяти (MPU) */
static void setup_mpu(void)
{
    mpu_region_config_t region_config = {0};

    /* Выключение MPU */
    hal_mpu_disable();

    /* Конфигурация области AXISRAM с максимальной производительностью  */
    region_config.enable = MPU_REGION_ENABLE;
    region_config.number = MPU_REGION_NUMBER0;
    region_config.base_address = 0x24010000;
    region_config.size = MPU_REGION_SIZE_512KB;
    region_config.subregion_disable = 0x00;
    region_config.type_extension_level = MPU_TEX_LEVEL1;
    region_config.access_permission = MPU_REGION_FULL_ACCESS;
    region_config.execute_enable = MPU_REGION_EXECUTE_ENABLE;
    region_config.is_shareable = MPU_REGION_NOT_SHAREABLE;
    region_config.is_cacheable = MPU_REGION_CACHEABLE;
    region_config.is_bufferable = MPU_REGION_BUFFERABLE;

    hal_mpu_region_init(&region_config);

    /* Конфигурация области XSPI2 */
    region_config.enable = MPU_REGION_ENABLE;
    region_config.number = MPU_REGION_NUMBER1;
    region_config.base_address = 0x70000000;
    region_config.size = MPU_REGION_SIZE_32MB;
    region_config.subregion_disable = 0x00;
    region_config.type_extension_level = MPU_TEX_LEVEL0;
    region_config.access_permission = MPU_REGION_FULL_ACCESS;
    region_config.execute_enable = MPU_REGION_EXECUTE_ENABLE;
    region_config.is_shareable = MPU_REGION_NOT_SHAREABLE;
    region_config.is_cacheable = MPU_REGION_CACHEABLE;
    region_config.is_bufferable = MPU_REGION_NOT_BUFFERABLE;

    hal_mpu_region_init(&region_config);

    /* Включение MPU */
    hal_mpu_enable(MPU_PRIVILEGED_DEFAULT);
}
/* ------------------------------------------------------------------------- */

/* Настройка и включение кэшей Cortex-M */
static void setup_cahce(void)
{
    /* Очистка кэша инструкций и кэша данных перед включением */
    SCB_InvalidateICache();
    SCB_InvalidateDCache();

    /* Включение кэша инструкций и кэша данных */
    SCB_EnableICache();
    SCB_EnableDCache();
}
/* ------------------------------------------------------------------------- */

static void jump_app(void)
{
    /* Отключение всех прерываний */
    __disable_irq();

    /* Синхронизация конвейера инструкций и данных */
    __ISB();
    __DSB();

    /* Определение типа указателя на функцию приложения */
    typedef void (*p_function)(void);

    /* Извлечение адреса точки входа приложения */
    p_function app = (p_function) * (uint32_t *) (APP_ADDRESS + 4);

    /* Установка основного указателя стека (MSP) */
    __set_MSP(*(uint32_t *) APP_ADDRESS);

    /* Переход к приложению */
    app();
}
/* ------------------------------------------------------------------------- */
