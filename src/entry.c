#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

#include "FreeRTOS.h"
#include "task.h"

#include "task_blinker.h"
#include "task_console.h"
#include "task_cyw43.h"
#include "task_network.h"
#include "task_heartbeat.h"
#include "global_signal.h"
#include "can.h"

// the magic global !
MainEnvironement_t MainEnvironement;

int gg(void)
{
	return (to_ms_since_boot(get_absolute_time()));
}

int main(void)
{
	printf("\nAt main entry %i", gg()); // no output !!!!

	stdio_init_all();

	printf("\nAfter init stdio %i", gg());

	int s = sizeof(can_msg_t);
	MainEnvironement.mainEventGroup = xEventGroupCreate();
	MainEnvironement.from_host = xQueueCreate( ITEMS_PER_QUEUE, s);
	MainEnvironement.to_host = xQueueCreate( ITEMS_PER_QUEUE, s);

	blinker_init(&MainEnvironement);
	console_init(&MainEnvironement);
	task_cyw43_init(&MainEnvironement);
	network_init(&MainEnvironement);
	heartbeat_init(&MainEnvironement);

	printf("\nBefore scheduler %i", gg());
	vTaskStartScheduler();

	puts("You should not be here!");

	return 0;
}
