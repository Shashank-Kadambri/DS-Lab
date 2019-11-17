#include <iostream>
#include <iomanip>
#include <limits>
#include "stack.h"

#define CLEAR_INPUT_BUFFER(c) \
    c.clear(); \
    c.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

bool areParenthesesBalanced(std::string&);

int main(void) {
    int choice;
    
    while(true) {
        std::cout << "\t\tPROGRAM TO MATCH PARENTHESES\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Enter the expression\n\t\t"
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
                std::cout << "\nEnter the expresssion: ";
                getline(std::cin, exp);
                if(areParenthesesBalanced(exp)) {
                    std::cout << "\nParentheses are balanced.\n";
                } else {
                    std::cout << "\nParentheses are not balanced.\n";
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

bool areParenthesesBalanced(std::string& exp) {
    Stack<char> stk;
    unsigned int len = exp.length();

    for(unsigned int i = 0; i < len; ++i) {
        if(exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {
            if(stk.push(exp[i]) == -1) {
                std::cout << "\n* Stack overflow *\n";
            }
        } else {
            switch(exp[i]) {
                case ')' : {
                    if(stk.top() == '(') {
                        if(stk.pop() == -1) {
                            std::cout << "\n* Stack underflow *\n";
                            return false;
                        }
                    } else {
                        return false;
                    }
                }
                break;

                case ']' : {
                    if(stk.top() == '[') {
                        if(stk.pop() == -1) {
                            std::cout << "\n* Stack underflow *\n";
                            return false;
                        }
                    } else {
                        return false;
                    }
                }
                break;

                case '}' : {
                   if(stk.top() == '{') {
                        if(stk.pop() == -1) {
                            std::cout << "\n* Stack underflow *\n";
                            return false;
                        }
                    } else {
                        return false;
                    } 
                }
                break;
            }
        }
    } 
    return stk.isEmpty();
}