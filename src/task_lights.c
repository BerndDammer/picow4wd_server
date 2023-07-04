#include <stdio.h>

#include "task_drive.h"
#include "task_prio.h"
#include "can.h"
#include "hardware_lights.h"

static TaskHandle_t lights_taskhandle;

#define POWER_OFF_DELAY_TICK pdMS_TO_TICKS(1000)

void lights_thread(MainEnvironement_t *MainEnvironement) {
	hardware_lights_init();

	while (true) {
		can_msg_t msg;
		BaseType_t result;

		result = xQueueReceive(MainEnvironement->to_lights, &msg,
		POWER_OFF_DELAY_TICK);
		if (result == pdPASS) {
			switch (msg.id) {
			case CAN___ID_LIGHTS:
				if (msg.len == 4 || msg.len == 8) {
					hardware_lights_set_single(msg.data[0], msg.data[1],
							msg.data[2], msg.data[3]);

				} else {
					puts("Wrong light len!");
				}
				break;
			default:
				puts("You should not be here");
				break;
			}
		} else if (result == errQUEUE_EMPTY) {
			hardware_lights_off();
		}
	}
}

void lights_init(MainEnvironement_t *MainEnvironement) {
	xTaskCreate((CALLEE) lights_thread, "LIGHTS", configMINIMAL_STACK_SIZE,
			MainEnvironement, LIGHTS_TASK_PRIO, &lights_taskhandle);
}
