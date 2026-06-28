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

#include "stm32h7rsxx_hal_def.h"
#include "FreeRTOS.h"
#include "task.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

#if defined DEBUG

/* Счетчик вызовов Idle Hook */
static uint32_t appl_idle_hook_counter = 0;

/* Текущий размер свободной кучи (байт) */
static size_t free_heap_size = 0;

/* Минимум свободной кучи за все время (байт) */
static size_t minimum_ever_free_heap_size = 0;

#endif /* DEBUG */

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

void vApplicationIdleHook(void)
{
#if defined DEBUG

    /* Увеличение счетчика вызовов Idle Hook */
    appl_idle_hook_counter++;

    /* Обновление значения размера свободной кучи */
    free_heap_size = xPortGetFreeHeapSize();

    /* Обновление значения минимума свободной кучи за все время */
    minimum_ever_free_heap_size = xPortGetMinimumEverFreeHeapSize();

#else

    /* Переход в энергосберегающий режим */
    __WFI();

#endif /* DEBUG */
}
/* ------------------------------------------------------------------------- */
