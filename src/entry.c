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
#include "global_signal.h"

int gg(void)
{
	return (to_ms_since_boot(get_absolute_time()));
}

int main(void)
{
	printf("\nAt main entry %i", gg()); // no output !!!!

	stdio_init_all();
	printf("\nAfter init stdio %i", gg());

	global_signal_init();

	blinker_init();
	console_init();
	task_cyw43_init();
	network_init();


	printf("\nBefore scheduler %i", gg());
	vTaskStartScheduler();

	puts("You should not be here!");

	return 0;
}
