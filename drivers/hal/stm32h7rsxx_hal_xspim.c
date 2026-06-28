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

#include "stm32h7rsxx_hal_xspim.h"

/* Private macros ---------------------------------------------------------- */

/* Значение времени между транзакциями регистра CR */
#define HAL_XSPIM_CR_REQ2ACK_TIME(time) \
    ((time) << XSPIM_CR_REQ2ACK_TIME_Pos)

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/*
 * Инициализация XSPIM
 *
 * Параметры: config - указатель на конфигурационную структуру XSPIM
 */
void hal_xspim_init(const xspim_config_t * config)
{
    /* Проверка входных параметров */
    assert(config != NULL);

    /* Настройка параметров XSPIM */
    XSPIM->CR = config->mux_enable          |
                config->mode                |
                config->override_ncs_enable |
                config->override_ncs_xspi1  |
                config->override_ncs_xspi2  |
                HAL_XSPIM_CR_REQ2ACK_TIME(config->req2ack_time);
}
/* ------------------------------------------------------------------------- */
