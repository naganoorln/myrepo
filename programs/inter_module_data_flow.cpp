// Module1 User Input
// Module2 Data Processing
// Module3 Send Data to server(printer)
#include <iostream>
#include <string>
using namespace std;
class Module1
{
    public:
        string getInput()
        {
            string input;
            getline(cin, input);
            return input;
        }
};
class Module2
{
    public:
        string processData(const string& input)
        {
            return "Processed Data: " + input;
        }
};
class Module3
{
    public:
        bool sendToPrinter(const string& data)
        {
            cout << "Sending to printer: " << endl;
            return true;
        }
        void handlePrintSuccess(bool success, const string& data)
        {
            if(success)
            {
                cout << "Print successful for: " << data << endl;
            } else {
                cout << "print failed for: " << data << endl;
        }
    }
};
int main()
{
    Module1 mod1;
    Module2 mod2;
    Module3 mod3;
    string userinput = mod1.getInput();
    const string processdata = mod2.processData(userinput);
    bool printsuccess = mod3.sendToPrinter(processdata);
    mod3.handlePrintSuccess(printsuccess, processdata);
    return 0;
}




