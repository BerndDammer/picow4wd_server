/*
 * task_blinker.c
 *
 *  Created on: 12.06.2023
 *      Author: manni4
 */

#include "task_blinker.h"
#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"
#include "task_prio.h"

static TaskHandle_t blinker_taskhandle;

#define PICO_DEFAULT_TOGGLE_PIN 16

void blinker_thread()
{
	gpio_init(PICO_DEFAULT_TOGGLE_PIN);
	gpio_set_dir(PICO_DEFAULT_TOGGLE_PIN, GPIO_OUT);

	while (true)
	{
		gpio_put(PICO_DEFAULT_TOGGLE_PIN, 1);
		vTaskDelay(25);
		gpio_put(PICO_DEFAULT_TOGGLE_PIN, 0);
		vTaskDelay(25);
	}
}

void blinker_init()
{
	xTaskCreate(blinker_thread, "BLINKER", configMINIMAL_STACK_SIZE, NULL,
			BLINKER_TASK_PRIO, &blinker_taskhandle);
}

