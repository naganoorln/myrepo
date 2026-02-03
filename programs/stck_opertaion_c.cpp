// Stack Operation
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;
bool is_operator(string& token)
{
    return token == "+" || token == "-" || token == "POP";
}
int process_tokens(const string& input)
{
    istringstream iss(input);
    stack <int> stk;
    string token;
    while(iss >> token) {
        if(isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
            int num = stoi(token);
            stk.push(num);
        } else if(is_operator(token)) {
            if(token == "+") {
                if(stk.size() < 2) {
                    return -1;
                }
                int operand2 = stk.top();
                stk.pop();
                int operand1 = stk.top();
                stk.pop();
                stk.push(operand1 + operand2);
            } else if(token == "-") {
                int operand2 = stk.top();
                stk.pop();
                int operand1 = stk.top();
                stk.pop();
                stk.push(operand1 - operand2);
            } else if(token == "POP") {
                if(!stk.empty()) {
                    stk.pop();
                } else {
                    return -1;
                }
            } else {
                return -1;
            }

        }

    }
    if(!stk.empty()) {
        return stk.top();
    } else {
        return -1;
    }
}
int main()
{
    string input = "65 5 4 21 + 8 21 - POP";
    int result = process_tokens(input);
    if(result != -1) {
        cout << "Reult: " << result << endl;
    } else {
        cerr << "Error: Invalid input or operation." << endl;
    }
    return 0;
}