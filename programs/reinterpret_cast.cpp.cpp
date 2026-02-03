#include <iostream>
#include <cstdint>
using namespace std;
#define GPIO_REG_ADDR 0x40020000

int main() {
    volatile uint32_t* GPIO_REG = reinterpret_cast<volatile uint32_t*>(GPIO_REG_ADDR);

    // Access the register as bytes
    volatile uint8_t* GPIO_BYTE = reinterpret_cast<volatile uint8_t*>(GPIO_REG);

    // Enable first and second byte
    GPIO_BYTE[0] = 0xFF;
    GPIO_BYTE[1] = 0xFF;
    cout << *GPIO_REG << endl;
    return 0;
}
