#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Define the size of the bitmap in bytes
#define BITMAP_SIZE 16  // For example, 16 bytes (128 bits)

// Function to initialize the bitmap
void initialize_bitmap(uint8_t *bitmap, size_t size) {
    memset(bitmap, 0, size); // Set all bits to 0 (all resources are free)
}

// Function to find the first free bit
int find_free_bit(const uint8_t *bitmap, size_t size) {
    for (size_t byte = 0; byte < size; ++byte) {
        for (size_t bit = 0; bit < 8; ++bit) {
            if (!(bitmap[byte] & (1 << bit))) {
                return byte * 8 + bit; // Return the position of the first free bit
            }
        }
    }
    return -1; // No free bit found
}

// Function to set a bit (allocate resource)
void set_bit(uint8_t *bitmap, int bit) {
    bitmap[bit / 8] |= (1 << (bit % 8)); // Set the bit to 1
}

// Function to clear a bit (deallocate resource)
void clear_bit(uint8_t *bitmap, int bit) {
    bitmap[bit / 8] &= ~(1 << (bit % 8)); // Clear the bit to 0
}

// Function to check if a bit is set
int is_bit_set(const uint8_t *bitmap, int bit) {
    return bitmap[bit / 8] & (1 << (bit % 8)); // Check if the bit is set to 1
}

int main() {
    uint8_t bitmap[BITMAP_SIZE];
    initialize_bitmap(bitmap, BITMAP_SIZE);

    printf("Initial bitmap:\n");
    for (int i = 0; i < BITMAP_SIZE; ++i) {
        printf("%02x ", bitmap[i]);
    }
    printf("\n");

    // Find and allocate a free bit
    int free_bit = find_free_bit(bitmap, BITMAP_SIZE);
    if (free_bit != -1) {
        printf("Allocating bit %d\n", free_bit);
    }

    // Print the bitmap after allocation
    printf("Bitmap after allocation:\n");
    for (int i = 0; i < BITMAP_SIZE; ++i) {
        printf("%02x ", bitmap[i]);
    }
    printf("\n");

    // Check if the bit is set
    if (is_bit_set(bitmap, free_bit)) {
        printf("Bit %d is set\n", free_bit);
    }

    // Deallocate the bit
    printf("Deallocating bit %d\n", free_bit);
    clear_bit(bitmap, free_bit);

    // Print the bitmap after deallocation
    printf("Bitmap after deallocation:\n");
    for (int i = 0; i < BITMAP_SIZE; ++i) {
        printf("%02x ", bitmap[i]);
    }
    printf("\n");

    return 0;
}