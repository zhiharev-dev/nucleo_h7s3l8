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

#include "FreeRTOS.h"
#include "task.h"

/* Variables --------------------------------------------------------------- */

#if defined(DEBUG)

/* Счетчик вызовов Idle Hook */
static uint32_t appl_idle_hook_counter = 0U;

/* Текущий размер свободной кучи (байт) */
static size_t free_heap_size = 0U;

/* Минимум свободной кучи за все время (байт) */
static size_t minimum_ever_free_heap_size = 0U;

#endif /* DEBUG */

/* User code --------------------------------------------------------------- */

void vApplicationIdleHook(void)
{
#if defined(DEBUG)

    appl_idle_hook_counter++;
    free_heap_size = xPortGetFreeHeapSize();
    minimum_ever_free_heap_size = xPortGetMinimumEverFreeHeapSize();

#endif /* DEBUG */
}
/* ------------------------------------------------------------------------- */
