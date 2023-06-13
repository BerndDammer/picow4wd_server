/*
 * task_blinker.c
 *
 *  Created on: 12.06.2023
 *      Author: manni4
 */

#include "task_blinker.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "task_prio.h"

static TaskHandle_t console_taskhandle;

static void console_menu()
{
	printf("\n\n");
	printf("------------------------------------\n");
	printf("LWIP and UDP Multicast Test\n");
	printf("a Show netif data\n");
	printf("h Show hostname data\n");
	printf("x hardware address\n");
	printf("press key to select\n");
	printf("------------------------------------\n");

}

void console_command(int c)
{
	switch (c)
	{
	case 'a':
	{
//					char buffer[STR_BUF_LEN];
//
//					ip4addr_ntoa_r(&netif_default->ip_addr, buffer,
//							STR_BUF_LEN);
//					printf("\nnetif.ip_addr %s", buffer);
//
//					ip4addr_ntoa_r(&netif_default->netmask, buffer,
//							STR_BUF_LEN);
//					printf("\nnetif.netmask %s", buffer);
//
//					ip4addr_ntoa_r(&netif_default->gw, buffer, STR_BUF_LEN);
//					printf("\nnetif.gw %s\n", buffer);
	}
		break;
	case 'x':
	{
//					printf("\nHardware address: ");
//					for (int i = 0; i < netif_default->hwaddr_len; i++)
//					{
//						printf("%02X", netif_default->hwaddr[i]);
//						if (i != netif_default->hwaddr_len - 1)
//						{
//							printf(":");
//						}
//					}
//					printf("\n");
	}
		break;
	case 'h':
	{
//					printf("\nhostname: %s\n", netif_default->hostname);
	}
		break;
	case ' ':
	default:
		console_menu();
		break;
	}
}

void console_thread()
{
	int c;

	console_menu();

	while (true)
	{
		vTaskDelay(100);
		bool working = true;
		while (working)
		{
			c = getchar_timeout_us(10);
			if (c != PICO_ERROR_TIMEOUT)
			{
				console_command(c);
			}
			else
			{
				working = false;
			}
		}
		//vTaskDelay(100);
	}
}

void console_init()
{
	xTaskCreate(console_thread, "CONSOLE", configMINIMAL_STACK_SIZE, NULL,
	BLINKER_TASK_PRIO, &console_taskhandle);
}

