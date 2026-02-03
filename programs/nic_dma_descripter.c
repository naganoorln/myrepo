#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define RING_SIZE 4
#define BUFFER_SIZE 64
#define OWN_BIT 0x1
#define NUM_PACKETS 6  /* number of packets to simulate */

/* RX Descriptor structure */
typedef struct 
{
	uint64_t buffer_addr;  /* pointer to packet buffer (simulated physical address) */
	uint32_t length;       /* buffer size */
	uint32_t status;       /* OWN bit + flags */
	uint32_t packet_info;  /* NIC metadata (length, checksum) */
} dma_desc;

/* Simulated NIC function to write packets into buffers */
void nic_receive_packet(dma_desc *rx_ring, uint8_t *buffers[], int ring_size, const char *packet, int packet_len) 
{
    static int nic_index = 0;  /* circular ring index */
	dma_desc *desc = &rx_ring[nic_index];

	if (desc->status & OWN_BIT) 
	{  /* NIC owns it, can write */
		int copy_len = (packet_len < desc->length) ? packet_len : desc->length;
		memcpy((void *)desc->buffer_addr, packet, copy_len); /* write packet to buffer */
		desc->packet_info = copy_len;       /* NIC metadata: packet length */
		desc->status &= ~OWN_BIT;           /* clear OWN bit, driver can read */

		printf("[NIC] Packet written to buffer %d, length %d\n", nic_index, copy_len);

		nic_index = (nic_index + 1) % ring_size; /* move to next descriptor (circular) */
	} else {
		printf("[NIC] Descriptor %d not available (OWN=0)\n", nic_index);
	}
}

/* Simulated driver function to process packets */
void driver_process_packets(dma_desc *rx_ring, uint8_t *buffers[], int ring_size) 
{
	for (int i = 0; i < ring_size; i++) 
	{
		dma_desc *desc = &rx_ring[i];
		if (!(desc->status & OWN_BIT)) 
		{  /* CPU owns it, packet ready */
			printf("[Driver] Processing buffer %d, packet length %d: ", i, desc->packet_info);
			for (int j = 0; j < desc->packet_info; j++)
				putchar(((char *)desc->buffer_addr)[j]);
			putchar('\n');

			desc->status = OWN_BIT; /* return ownership to NIC */
		}
	}
}

int main() {
	/* Step 1: Allocate buffers */
	uint8_t *rx_buffers[RING_SIZE];
	for (int i = 0; i < RING_SIZE; i++) 
	{
		rx_buffers[i] = malloc(BUFFER_SIZE);
		memset(rx_buffers[i], 0, BUFFER_SIZE);
	}

	/* Step 2: Allocate RX descriptor ring */
	dma_desc rx_ring[RING_SIZE];

	/* Step 3: Fill descriptors with buffer addresses and length, set OWN_BIT */
	for (int i = 0; i < RING_SIZE; i++) 
	{
		rx_ring[i].buffer_addr = (uint64_t)rx_buffers[i];  /* simulation */
		rx_ring[i].length = BUFFER_SIZE;
		rx_ring[i].status = OWN_BIT;  /* NIC owns it initially */
		rx_ring[i].packet_info = 0;
	}

	/* Simulated incoming packets */
	const char *packets[NUM_PACKETS] = {
		"Hello",
		"World",
		"This",
		"Is",
		"RX",
		"Simulation"
	};

	printf("=== RX Ring Simulation Start ===\n");

	/* Step 4: NIC receives packets and driver processes them */
	for (int i = 0; i < NUM_PACKETS; i++) 
	{
		printf("\n--- Incoming packet %d ---\n", i+1);
		nic_receive_packet(rx_ring, rx_buffers, RING_SIZE, packets[i], (int)strlen(packets[i]));
		driver_process_packets(rx_ring, rx_buffers, RING_SIZE);
	}

	/* Free buffers */
	for (int i = 0; i < RING_SIZE; i++)
		free(rx_buffers[i]);

	printf("\n=== RX Ring Simulation End ===\n");
	return 0;
}
/*RX Ring Buffer Flow — Step by Step
We’ll follow driver → physical memory → NIC → driver.
________________________________________
Step 1: Allocate RX Ring Memory (Descriptor Ring)
•The driver allocates a contiguous array of RX descriptors in DMA-capable memory:
#define RING_SIZE 128
struct dma_desc *rx_ring;
dma_addr_t rx_ring_phys;
rx_ring = dma_alloc_coherent(dev, RING_SIZE * sizeof(struct dma_desc), &rx_ring_phys, GFP_KERNEL);
•rx_ring → virtual address the CPU can use.
•rx_ring_phys → physical address the NIC can use.
Analogy: CPU creates a set of index cards, one for each buffer, and places them in a mailbox the NIC can reach.
________________________________________
Step 2: Allocate Buffers for Each Descriptor
•Each descriptor points to a separate packet buffer:
uint8_t *rx_buffers[RING_SIZE];
for (int i = 0; i < RING_SIZE; i++) 
{
    rx_buffers[i] = kmalloc(BUFFER_SIZE, GFP_KERNEL);  // CPU virtual address
    uint64_t phys_addr = dma_map_single(dev, rx_buffers[i], BUFFER_SIZE, DMA_FROM_DEVICE);
    rx_ring[i].buffer_addr = phys_addr; // NIC will DMA packet here
    rx_ring[i].length = BUFFER_SIZE;
    rx_ring[i].status = OWN_BIT;        // NIC owns descriptor
}
•CPU fills input fields: buffer_addr, length, status.
•Each buffer_addr points to a separate DMA-able memory area for the packet.
Analogy: Each card in the mailbox tells the truck “Deliver letter here, envelope is this big”.
________________________________________
Step 3: Inform NIC About Descriptor Ring
•NIC needs to know where the descriptor ring starts and its size:
write_register(dev, RX_RING_BASE_ADDR, rx_ring_phys); // physical address
write_register(dev, RX_RING_LENGTH, RING_SIZE);
write_register(dev, RX_RING_TAIL, RING_SIZE - 1);     // ready to consume
•Now NIC can scan the descriptor ring physically.
Analogy: You give the truck the GPS coordinates of the mailbox and the number of cards inside.
________________________________________
Step 4: NIC Scans and Consumes Descriptors
•NIC loops over descriptors with OWN=1:
for each descriptor in rx_ring:
    if OWN_BIT == 1:
        read buffer_addr, length
        DMA packet into buffer
        set OWN_BIT = 0
•Writes packet into the buffer memory (pointed by buffer_addr).
•Updates status with metadata like packet length, checksum, errors, VLAN info.
Analogy: Truck reads card, delivers packet into envelope, marks card as “done.”
________________________________________
Step 5: Driver Reads Packets
•Driver periodically or on interrupt checks descriptors:
for (int i = 0; i < RING_SIZE; i++) {
    if (!(rx_ring[i].status & OWN_BIT)) {  // NIC done
        process_packet(rx_buffers[i]);    // CPU reads virtual buffer
        rx_ring[i].status = OWN_BIT;      // give it back to NIC
    }
}
•CPU uses virtual addresses of buffers to read packet data.
•CPU then returns ownership by setting OWN=1 so NIC can reuse buffer.
Analogy: You read the delivered letter from envelope, mark the card “available again,” ready for next packet.
________________________________________
Step 6: Ring Wrap-Around (Circular Buffer)
•Descriptor ring is circular: after NIC reaches last descriptor, it wraps back to the first.
•Driver also wraps its index when reading.
Index: 0 → 1 → 2 → … → RING_SIZE-1 → 0 → 1 → ...
•This ensures continuous reception without memory reallocation.
________________________________________
Step 7: Summary Table
Step	Driver / CPU	NIC / Hardware
1	Allocates descriptor ring (virtual)	N/A
2	Allocates packet buffers, fills descriptor fields	Reads descriptors (physical addresses)
3	Writes RX_RING_BASE_ADDR register	Now knows where descriptors start
4	N/A	DMA writes packets into buffers, fills metadata, clears OWN
5	Reads buffer data when OWN=0	N/A
6	Sets OWN=1 to return descriptor	Scans next descriptor
________________________________________

Key Takeaways
1.	Descriptor ring memory is shared: CPU uses virtual address, NIC uses physical.
2.	Packet buffers are separate memory blocks, pointed to by buffer_addr.
3.	Ownership bit ensures safe access.
4.	Ring buffer allows continuous reception without reallocating memory.
5.	NIC fills output fields like status and packet_info; driver fills input fields like buffer_addr and length.
*/



