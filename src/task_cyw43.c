/*
 * async_cyw43.c
 *
 *  Created on: 28.04.2023
 *      Author: manni4
 */

#include "pico/cyw43_arch.h"

#include "pico/async_context.h"

#include "task_cyw43.h"
#include "parameter.h"
#include "panic.h"

#include "FreeRTOS.h"
#include "task.h"
#include "task_prio.h"

#include "global_signal.h"

#define CONNECT_TIMEOUT_MS 10000

static TaskHandle_t cyw43_init_taskhandle;

void thread_cyw43_init()
{
	if (cyw43_arch_init_with_country(CYW43_COUNTRY_GERMANY))
	{
		app_panic("cyw43 init failed");
		return;
	}

	xEventGroupSetBits(mainEventGroup, EVENT_MASK_CYW43_INIT);

	cyw43_arch_enable_sta_mode();

	if (cyw43_arch_wifi_connect_timeout_ms(PARA_SSID, PARA_PWD,
	CYW43_AUTH_WPA2_AES_PSK, CONNECT_TIMEOUT_MS))
	{
		xEventGroupSetBits(mainEventGroup, EVENT_MASK_FAIL);
		cyw43_arch_deinit();
		app_panic("failed to connect");
		return;
	}

	xEventGroupSetBits(mainEventGroup, EVENT_MASK_CONNECTED);
	printf("Connected.\n");

	while (1)
	{
		// everythings OK here
		vTaskDelay(1333);
	}
}

void task_cyw43_init(void)
{
	xTaskCreate(thread_cyw43_init, "CYW43_INIT", configMINIMAL_STACK_SIZE, NULL,
	CYW43_INIT_TASK_PRIO, &cyw43_init_taskhandle);
}

