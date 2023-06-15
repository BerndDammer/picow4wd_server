#include "global_signal.h"


EventGroupHandle_t mainEventGroup;

void global_signal_init(void)
{
	mainEventGroup = xEventGroupCreate();
}
