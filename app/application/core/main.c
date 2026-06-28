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
#include "gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

#define VTOR_ADDRESS    (0x70000000UL)

#define SYSTEM_CLOCK    (600000000UL)

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

static void system_init(void);

static void setup_vector_table(void);

static void app_main(void * argv);

/* Private user code ------------------------------------------------------- */

int main(void)
{
    system_init();

    if (xTaskCreate(app_main,
                   "app_main",
                    256,
                    NULL,
                    tskIDLE_PRIORITY + 1,
                    NULL) != pdPASS)
    {
        error();
    }

    vTaskStartScheduler();
}
/* ------------------------------------------------------------------------- */

void error(void)
{
    /* Отключение всех прерываний */
    __disable_irq();

    /* Выключение светодиодов */
    led_off(&led_green);
    led_off(&led_yellow);
    led_off(&led_red);

    /* Бесконечный цикл остановки системы */
    while (true)
    {
        /* Мигание светодиода - индикация состояния "Ошибка" */
        for (uint32_t i = 0; i < 60000; i++)
        {
            for (uint32_t j = 0; j < 500; j++) __NOP();
        }

        /* Изменение состояние светодиода */
        led_toggle(&led_red);
    }
}
/* ------------------------------------------------------------------------- */

static void app_main(void * argv)
{
    static const TickType_t frequency = pdMS_TO_TICKS(10);

    TickType_t last_wake_time = xTaskGetTickCount();

    /* INIT USER CODE BEGIN ------------------------------------------------ */

    /* Включение светодиода - индикация состояния "Работа" */
    led_on(&led_green);

    /* INIT USER CODE END -------------------------------------------------- */

    while (true)
    {
        vTaskDelayUntil(&last_wake_time, frequency);
    }

    vTaskDelete(NULL);
}
/* ------------------------------------------------------------------------- */

static void system_init(void)
{
    setup_vector_table();

    systick_init(SYSTEM_CLOCK);
    gpio_init();
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
