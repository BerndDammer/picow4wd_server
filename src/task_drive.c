/*
 * task_drive.c
 *
 *  Created on: 20.06.2023
 *      Author: manni4
 */

#include "task_drive.h"
#include "task_prio.h"
#include "can.h"

static TaskHandle_t drive_taskhandle;

void drive_thread(MainEnvironement_t *MainEnvironement)
{
	while (true)
	{
		can_msg_t msg;
		BaseType_t result;

		result = xQueueReceive(MainEnvironement->to_drive, &msg, XDELAY);
		if (result == pdPASS)
		{
		}
		else if (result == errQUEUE_EMPTY)
		{
		}
	}
}

void drive_init(MainEnvironement_t *MainEnvironement)
{
	xTaskCreate((CALLEE) drive_thread, "DRIVE", configMINIMAL_STACK_SIZE,
			MainEnvironement, DRIVE_TASK_PRIO, &drive_taskhandle);
}
