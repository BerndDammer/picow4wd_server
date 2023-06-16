#include "global_signal.h"

// TRAP: the top 8 bits are forbidden

EventGroupHandle_t mainEventGroup;

void global_signal_init(void)
{
	mainEventGroup = xEventGroupCreate();
}
