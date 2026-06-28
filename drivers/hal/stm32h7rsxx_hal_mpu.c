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

#include "stm32h7rsxx_hal_mpu.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/*
 * Инициализация области MPU
 *
 * Параметры: config - указатель на конфигурационную структуру области MPU
 */
void hal_mpu_region_init(const mpu_region_config_t * config)
{
    /* Проверка входных параметров */
    assert(config != NULL);

    /* Установка номера области */
    MPU->RNR = config->number;

    /* Выключение области перед настройкой */
    MPU->RASR &= ~MPU_RASR_ENABLE_Msk;

    /* Установка адреса области */
    MPU->RBAR = config->base_address;

    /* Настройка параметров области */
    MPU->RASR = config->execute_enable       |
                config->access_permission    |
                config->type_extension_level |
                config->is_shareable         |
                config->is_cacheable         |
                config->is_bufferable        |
                config->subregion_disable    |
                config->size                 |
                config->enable;
}
/* ------------------------------------------------------------------------- */

/*
 * Включение MPU
 *
 * Параметры: mpu_control - управление режимом HFNMI и доступом привилегированного режима
 */
void hal_mpu_enable(uint32_t mpu_control)
{
    /* Настройка и включение MPU */
    MPU->CTRL = mpu_control | MPU_CTRL_ENABLE_Msk;

    /* Включение обработчиков ошибок */
    SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;

    /* Сброс конвейера инструкций и данных */
    __DSB();
    __ISB();
}
/* ------------------------------------------------------------------------- */

/* Выключение MPU */
void hal_mpu_disable(void)
{
    /* Сброс конвейера данных */
    __DMB();

    /* Отключение обработчиков ошибок */
    SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;

    /* Выключение MPU и сброс регистра управления */
    MPU->CTRL = 0U;
}
/* ------------------------------------------------------------------------- */
