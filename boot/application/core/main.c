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

/* Constants --------------------------------------------------------------- */

#define VTOR_ADDRESS    (0x08000000UL)

#define HSI_CLOCK       (64000000UL)

/* Function prototypes ----------------------------------------------------- */

static void system_init(void);

static void setup_vector_table(void);

static void setup_fpu(void);

static void app_main(void);

/* User code --------------------------------------------------------------- */

int main(void)
{
    system_init();
    app_main();
}
/* ------------------------------------------------------------------------- */

void error(void)
{
    __disable_irq();

    while (true);
}
/* ------------------------------------------------------------------------- */

static void app_main(void)
{
    while (true);
}
/* ------------------------------------------------------------------------- */

static void system_init(void)
{
    setup_vector_table();
    setup_fpu();

    systick_init(HSI_CLOCK);
}
/* ------------------------------------------------------------------------- */

static void setup_vector_table(void)
{
    /* Запрет прерываний (начало критической секции) */
    __disable_irq();

    /* Установка адреса таблицы векторов */
    SCB->VTOR = VTOR_ADDRESS;

    /* Синхронизация памяти */
    __DSB();
    __ISB();

    /* Восстановление прерываний (завершение критической секции) */
    __enable_irq();
}
/* ------------------------------------------------------------------------- */

static void setup_fpu(void)
{
    /* Включение доступа к сопроцессорам FPU */
    SCB->CPACR |= (0x3U << 20U) | (0x3U << 22U);

    /* Синхронизация памяти */
    __DSB();
    __ISB();
}
/* ------------------------------------------------------------------------- */
