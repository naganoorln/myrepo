#include <iostream>
#include <bitset>
using namespace std;
class SixBitData
{
    private:
        unsigned char data;
    public:
        SixBitData():data(0){}
        void setValue(int value)
        {
            if(value > 63)
            {
                throw
                out_of_range("value must be between 0 and 63");
                
            }
            data = value & 0x3F;
        }
        unsigned int getValue()
        {
            return data;
        }
        void printBinary()
        {
            bitset<8> binary(data);
            cout << "Binary Data: " << binary << endl;
        }
};

int main()
{
    SixBitData bitdata;
    try
    {
        bitdata.setValue(45);
        cout << "Get value: " << bitdata.getValue() << endl;
        bitdata.printBinary();
        bitdata.setValue(70);
        cout << "Get value: " << bitdata.getValue() << endl;
    }
    catch(const out_of_range& e)
    {
        cerr << "Err: " << e.what() << endl;
    }
    return 0;
}