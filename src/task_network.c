#include "task_network.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "FreeRTOS.h"
#include "task.h"
#include "task_prio.h"

#include "global_signal.h"
#include "can.h"
//#include "async_heartbeat.h"

static TaskHandle_t network_taskhandle;

#define UDP_PORT_RECEIVE 50000
#define UDP_PORT_TRANS   50100
#define HEARTBEAT_TIMEOUT_MS 1000

// thats magic
//extern struct netif gnetif;

void recCallBack(void *vp, struct udp_pcb *pcb, struct pbuf *p,
		const ip_addr_t *addr, u16_t port)
{
	// is ok for FreeRTOS function
	// or from ISR ????
	MainEnvironement_t *MainEnvironement = (MainEnvironement_t*) vp;
	if (p->len == sizeof(can_msg_t))
	{
		xQueueSend(MainEnvironement->from_host, p->payload, XDELAY);
		// should return immediately
	}
	else
	{
		printf("\np ->len %i", p->len);
	}
	pbuf_free(p);
}

void network_thread(MainEnvironement_t *MainEnvironement)
{
	struct udp_pcb *broadcast_receive_socket;
	ip4_addr_t broadcast_destination;

	EventBits_t bits = 0;
	int reciece_counter = 0;

	// wait for connection
	while (!(bits & EVENT_MASK_CONNECTED))
	{
		bits = xEventGroupWaitBits(MainEnvironement->mainEventGroup,
		EVENT_MASK_CONNECTED,
		pdFALSE,
		pdFALSE, 10000);
	}

	IP4_ADDR(&broadcast_destination, 255, 255, 255, 255); //non routing local broadcast
	broadcast_receive_socket = udp_new();

	udp_bind(broadcast_receive_socket, NULL, UDP_PORT_RECEIVE); //to allow receiving multicast
	udp_recv(broadcast_receive_socket, recCallBack, MainEnvironement); //recCallBack is the callback function that will be called every time you    receive multicast

	while (true)
	{
		can_msg_t msg;
		BaseType_t result;

		// TODO: what triggers a package send ????
		result = xQueueReceive(MainEnvironement->to_host, &msg, XDELAY);

		if (result == pdPASS)
		{
			struct pbuf *p;
			p = pbuf_alloc(PBUF_TRANSPORT, sizeof(can_msg_t), PBUF_RAM);
			memcpy(p->payload, &msg, sizeof(can_msg_t));

			udp_sendto(broadcast_receive_socket, p, &broadcast_destination,
			UDP_PORT_TRANS); //send a multicast packet
			pbuf_free(p);
		}
		else
		{
			puts("You should not be here");
		}
	}
}

void network_init(MainEnvironement_t *MainEnvironement)
{
	xTaskCreate((CALLEE) network_thread, "NETWORK", configMINIMAL_STACK_SIZE,
			MainEnvironement,
			NETWORK_TASK_PRIO, &network_taskhandle);
}

