#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

#include "FreeRTOS.h"
#include "task.h"

#include "task_blinker.h"

int main()
{
	stdio_init_all();

	blinker_init();
	vTaskStartScheduler();

	puts("You should not be here!");

	return 0;
}
