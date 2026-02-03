#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#define PACKET_SIZE 64
#define RING_SIZE 8

// Status flags
#define NIC_OWNED 0x1
#define DRIVER_OWNED 0x2

//Descriptor structure
typedef struct
{
	volatile uint32_t status; // Status flags-defined above
	uint32_t length; // Packet length
	uint8_t* buffer_addr; // Buffer pointer
} Descriptor;

// Ring buffer structure
typedef struct
{
	Descriptor descriptor[RING_SIZE];
	int head; // Driver,s read position
	int tail; // NIC write position
} RingBuffer;

void initializeRingBuffer(RingBuffer* ring)
{
	for(int i = 0; i < RING_SIZE; i++)
	{
		ring->descriptor[i].buffer_addr = malloc(PACKET_SIZE);
		ring->descriptor[i].status = NIC_OWNED;
	}
	ring->head = ring->tail = 0;
}

void nicWrite(RingBuffer* ring)
{
	if(ring->descriptor[ring->tail].status == DRIVER_OWNED)
	{
		printf("[NIC] Ring buffer full! Can not write packet.\n");
		return;
	}
	// Generate randam packet
	char packet[PACKET_SIZE];
	int len = snprintf(packet, PACKET_SIZE, "Packet-%d", rand() % 1000);
	Descriptor* desc = &ring->descriptor[ring->tail];
	memcpy(desc->buffer_addr, packet, len);
	desc->length = len;
	desc->status = DRIVER_OWNED;
	printf("[NIC] wrote packet at index %d, length: %d, data: %s\n",ring->tail, len, packet);
	ring->tail = (ring->tail + 1) % RING_SIZE;
}

void driverRead(RingBuffer* ring)
{
	if(ring->descriptor[ring->head].status == NIC_OWNED)
	{
		printf("[DRIVER] No new packets to read.\n");
		return;
	}
	Descriptor* desc = &ring->descriptor[ring->head];
	printf("[Driver] Read packet at index %d, length: %d, data: %s\n", ring->head, desc->length, desc->buffer_addr);
	desc->status = NIC_OWNED;
	ring->head = (ring->head + 1) % RING_SIZE;
}

int main()
{
	RingBuffer ring;
	initializeRingBuffer(&ring);
	while(1)
	{
		nicWrite(&ring);
		driverRead(&ring);
		usleep(500000);
	}
	return 0;
}

