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

#include "stm32h7rsxx_hal_pwr.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/*
 * Инициализация PWR
 *
 * Параметры: config - указатель на конфигурационную структуру PWR
 */
void hal_pwr_init(const pwr_config_t * config)
{
    /* Проверка входных параметров */
    assert(config != NULL);

    /* Отключение защиты записи резервного домена */
    PWR->CR1 |= PWR_CR1_DBP_Msk;

    /* Запись конфигурации источника питания */
    PWR->CSR2 = config->supply;

    /* Ожидание готовности источника питания */
    while ((PWR->SR1 & PWR_SR1_ACTVOSRDY_Msk) == 0U);

    /* Настройка VOS */
    PWR->CSR4 = config->vos;

    /* Ожидание готовности VOS */
    while ((PWR->CSR4 & PWR_CSR4_VOSRDY_Msk) == 0U);

    /* Настройка состояния XSPIM2 */
    PWR->CSR2 = config->xspim2_enable;
}
/* ------------------------------------------------------------------------- */
