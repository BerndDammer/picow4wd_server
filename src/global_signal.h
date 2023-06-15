/*
 * task_blinker.h
 *
 *  Created on: 12.06.2023
 *      Author: manni4
 */

#ifndef GLOBAL_SIGNAL_H_
#define GLOBAL_SIGNAL_H_

#include "FreeRTOS.h"
#include "event_groups.h"

extern EventGroupHandle_t mainEventGroup;
void global_signal_init(void);

#define EVENT_MASK_CONSOLE_CHAR 0X400000


#endif /* GLOBAL_SIGNAL_H_ */
