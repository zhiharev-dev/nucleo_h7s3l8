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

/* User code --------------------------------------------------------------- */

void nmi_handler(void)
{
    error();
}
/* ------------------------------------------------------------------------- */

void hard_fault_handler(void)
{
    error();
}
/* ------------------------------------------------------------------------- */

void mem_manage_handler(void)
{
    error();
}
/* ------------------------------------------------------------------------- */

void bus_fault_handler(void)
{
    error();
}
/* ------------------------------------------------------------------------- */

void usage_fault_handler(void)
{
    error();
}
/* ------------------------------------------------------------------------- */

void systick_handler(void)
{
    systick_it_handler();
}
/* ------------------------------------------------------------------------- */
