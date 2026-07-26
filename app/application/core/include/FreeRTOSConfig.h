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

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>

    void xPortSysTickHandler( void );

    #define vPortSVCHandler svc_handler
    #define xPortPendSVHandler pend_sv_handler
#endif

#define configUSE_PREEMPTION                            (1U)
#define configCPU_CLOCK_HZ                              (600000000UL)
#define configTICK_RATE_HZ                              (1000U)
#define configMAX_PRIORITIES                            (5U)
#define configMINIMAL_STACK_SIZE                        (256U)
#define configTOTAL_HEAP_SIZE                           (32768U)
#define configTICK_TYPE_WIDTH_IN_BITS                   TICK_TYPE_WIDTH_32_BITS

#define configUSE_IDLE_HOOK                             (1U)
#define configUSE_TICK_HOOK                             (0U)
#define configUSE_MALLOC_FAILED_HOOK                    (0U)
#define configCHECK_FOR_STACK_OVERFLOW                  (0U)

#define configUSE_TIME_SLICING                          (1U)

#define configUSE_MUTEXES                               (1U)
#define configUSE_COUNTING_SEMAPHORES                   (1U)

#define configSUPPORT_STATIC_ALLOCATION                 (0U)
#define configSUPPORT_DYNAMIC_ALLOCATION                (1U)

#define configUSE_TIMERS                                (1U)
#define configTIMER_TASK_PRIORITY                       (2U)
#define configTIMER_QUEUE_LENGTH                        (10U)
#define configTIMER_TASK_STACK_DEPTH                    (256U)

#define configPRIO_BITS                                 (4U)
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         (15U)
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    (5U)
#define configKERNEL_INTERRUPT_PRIORITY                 ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << ( 8U - configPRIO_BITS ) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY            ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << ( 8U - configPRIO_BITS ) )

#define INCLUDE_vTaskPrioritySet                        (1U)
#define INCLUDE_uvTaskPriorityGet                       (1U)
#define INCLUDE_vTaskDelete                             (1U)
#define INCLUDE_vTaskSuspend                            (1U)
#define INCLUDE_vTaskDelay                              (1U)
#define INCLUDE_vTaskDelayUntil                         (1U)
#define INCLUDE_xTaskGetCurrentTaskHandle               (1U)
#define INCLUDE_xTaskGetSchedulerState                  (1U)
#define INCLUDE_xTimerPendFunctionCall                  (1U)
#define INCLUDE_xEventGroupSetBitFromISR                (1U)

#define configASSERT( x )                               if ( ( x ) == 0U ) { taskDISABLE_INTERRUPTS(); for( ;; ) {} }

#endif /* FREERTOS_CONFIG_H */
