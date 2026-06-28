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

#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

/* Macros ------------------------------------------------------------------ */

/* Constants --------------------------------------------------------------- */

/* Types ------------------------------------------------------------------- */

/* Variables --------------------------------------------------------------- */

char *__env[1] = { 0 };
char **environ = __env;

/* Function prototypes ----------------------------------------------------- */

extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));

/* User code --------------------------------------------------------------- */

void initialise_monitor_handles(void)
{

}
/* ------------------------------------------------------------------------- */

int _getpid(void)
{
    return 1;
}
/* ------------------------------------------------------------------------- */

int _kill(int pid, int sig)
{
    (void) pid;
    (void) sig;

    errno = EINVAL;

    return -1;
}
/* ------------------------------------------------------------------------- */

void _exit(int status)
{
    (void) status;

    _kill(status, -1);

    while (1) { }
}
/* ------------------------------------------------------------------------- */

__attribute__((weak))
int _read(int file, char * ptr, int len)
{
    (void) file;

    if (__io_getchar == NULL)
    {
        errno = ENOSYS;

        return -1;
    }

    for (int data_id = 0; data_id < len; data_id++)
    {
        *ptr++ = __io_getchar();
    }

    return len;
}
/* ------------------------------------------------------------------------- */

__attribute__((weak))
int _write(int file, char * ptr, int len)
{
    (void) file;

    if (__io_putchar == NULL)
    {
        errno = ENOSYS;

        return -1;
    }

    for (int data_id = 0; data_id < len; data_id++)
    {
        __io_putchar(*ptr++);
    }

    return len;
}
/* ------------------------------------------------------------------------- */

int _close(int file)
{
    (void) file;

    return -1;
}
/* ------------------------------------------------------------------------- */

int _fstat(int file, struct stat * st)
{
    (void) file;

    st->st_mode = S_IFCHR;

    return 0;
}
/* ------------------------------------------------------------------------- */

int _isatty(int file)
{
    (void) file;

    return 1;
}
/* ------------------------------------------------------------------------- */

int _lseek(int file, int ptr, int dir)
{
    (void) file;
    (void) ptr;
    (void) dir;

    return 0;
}
/* ------------------------------------------------------------------------- */

int _open(const char * path, int flags, ...)
{
    (void) path;
    (void) flags;

    errno = ENOENT;

    return -1;
}
/* ------------------------------------------------------------------------- */

int _stat(const char * file, struct stat * st)
{
    (void) file;

    st->st_mode = S_IFCHR;

    return 0;
}
/* ------------------------------------------------------------------------- */

int _unlink(const char * name)
{
    (void) name;

    errno = ENOENT;

    return -1;
}
/* ------------------------------------------------------------------------- */

int _wait(int * status)
{
    (void) status;

    errno = ECHILD;

    return -1;
}
/* ------------------------------------------------------------------------- */

int _times(struct tms * buf)
{
    (void) buf;

    return -1;
}
/* ------------------------------------------------------------------------- */

int _link(const char * old, const char * new)
{
    (void) old;
    (void) new;

    errno = EMLINK;

    return -1;
}
/* ------------------------------------------------------------------------- */

int _fork(void)
{
    errno = EAGAIN;

    return -1;
}
/* ------------------------------------------------------------------------- */

int _execve(const char * name, char * const * argv, char * const * env)
{
    (void) name;
    (void) argv;
    (void) env;

    errno = ENOMEM;

    return -1;
}
/* ------------------------------------------------------------------------- */
