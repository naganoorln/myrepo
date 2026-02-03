#include <iostream>
#include <cstdint>
using namespace std;
int main()
{
    uint32_t regvalue = 0x11223344;
    uint32_t* regptr = reinterpret_cast<uint32_t*>(&regvalue);
    uint8_t* regptr8 = reinterpret_cast<uint8_t*>(regptr);
    if(regptr8[0] == 0x11)
    {
        cout << "Big Endian" << endl;
        
    }
    cout << hex << regvalue << endl;
    return 0;
}