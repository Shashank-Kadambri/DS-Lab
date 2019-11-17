#include <iostream>
#include <limits>
#include <iomanip>
#include <cctype>
#include <cmath>
#include "stack.h"

#define CLEAR_INPUT_BUFFER(c) \
    c.clear(); \
    c.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

int postfixEvaluator(std::string&);
bool isOperator(char);

int main(void) {
    int choice;

    while(true) {
        std::cout << "\t\tPROGRAM TO EVALUATE POSTFIX EXPRESSION\n\n\t\t"
            << "----------MENU----------\n\t\t"
            << "1. Enter the postfix expression\n\t\t"
            << "2. Exit the program\n\n"
            << "Enter your choice: ";
        while(!(std::cin >> choice) || !(choice == 1 || choice == 2)) {
            CLEAR_INPUT_BUFFER(std::cin);
            std::cout << "Please enter a valid choice: ";
        }
        CLEAR_INPUT_BUFFER(std::cin);
        switch(choice) {
            case 1 : {
                std::string exp;
                std::cout << "\nEnter the postfix expression: ";
                getline(std::cin, exp);
                int result = postfixEvaluator(exp);
                if(result == __INT_MAX__) {
                    std::cout << "\nPostfix expression is invalid!\n";
                    exit(-1);
                } else {
                    std::cout << "\nResult = " << result;
                }
            }
            break;

            case 2 : {
                char ch;

                std::cout << "\nSure to exit? (Y/N): ";
                std::cin >> ch;
                if(tolower(ch) == 'y') {
                    exit(0);
                } else {
                    std::cout << "\n\n";
                    std::cout << std::setw(80) << std::setfill('*');
                    std::cout << "\n\n" << std::endl;
                    continue;
                }
            }
            break;
        }
        std::cout << "\n\n";
        std::cout << std::setw(80) << std::setfill('*');
        std::cout << "\n\n" << std::endl;
    }
    return 0;
}

int postfixEvaluator(std::string& s) {
    Stack<int> stk;
    int op1, op2;
    unsigned int len = s.length();

    for(unsigned int i = 0; i < len; ++i) {
        if(isdigit(s[i])) {
            stk.push(static_cast<int>(s[i]) - 48);
        } else if(isOperator(s[i])) {
            switch(s[i]) {
                case '^' : {
                    op2 = stk.top();
                    stk.pop();
                    op1 = stk.top();
                    stk.pop();
                    stk.push(pow(op1, op2));
                }
                break;

                case '*' : {
                    op2 = stk.top();
                    stk.pop();
                    op1 = stk.top();
                    stk.pop();
                    stk.push(op1 * op2);
                }
                break;

                case '/' : {
                    op2 = stk.top();
                    stk.pop();
                    op1 = stk.top();
                    stk.pop();
                    stk.push(op1 / op2);
                }
                break;

                case '+' : {
                    op2 = stk.top();
                    stk.pop();
                    op1 = stk.top();
                    stk.pop();
                    stk.push(op1 + op2);
                }
                break;

                case '-' : {
                    op2 = stk.top();
                    stk.pop();
                    op1 = stk.top();
                    stk.pop();
                    stk.push(op1 - op2);
                }
                break;
            }
        } else {
            return __INT_MAX__;
        }
    }
    int res = stk.top();
    stk.pop();
    if(stk.isEmpty())
        return res;
    else
        return __INT_MAX__;    
}

bool isOperator(char ch) {
    switch(ch) {
        case '^' :
        case '*' :
        case '/' :
        case '+' :
        case '-' : return true;
                    break;
        default : return false; 
    }
}