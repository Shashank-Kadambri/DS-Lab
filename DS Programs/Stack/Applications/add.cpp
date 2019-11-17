#include <iostream>
#include <limits>
#include "stack.h"

#define CLEAR_INPUT_BUFFER(c) \
    c.clear(); \
    c.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

void inputNumber(Stack<int>&);
Stack<int> addStackNumbers(Stack<int>&, Stack<int>&);
void clearStack(Stack<int>&);

int main(void) {
    Stack<int> stk1, stk2;
    int choice;

    while(true) {
        std::cout << "\t\tPROGRAM TO ADD TWO LARGE NUMBERS\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Enter the numbers\n\t\t"
                << "2. Exit the program\n\n"
                << "Enter your choice: ";
        while(!(std::cin >> choice) || !(choice == 1 || choice == 2)) {
            CLEAR_INPUT_BUFFER(std::cin);
            std::cout << "Please enter a valid choice: ";
        }
        switch(choice) {
            case 1 : {
                std::cout << "\nEnter the first number digit-by-digit (-1 to terminate):\n";
                inputNumber(stk1);
                std::cout << "\nEnter the second number digit-by-digit (-1 to terminate):\n";
                inputNumber(stk2);
                std::cout << "\nFirst number:  ";
                stk1.print(2);
                std::cout << "\nSecond number: ";
                stk2.print(2);
                Stack<int> stk3 = addStackNumbers(stk1, stk2);
                std::cout << "\n\nAddition result: ";
                stk3.print(3);
                clearStack(stk1);
                clearStack(stk2);
                clearStack(stk3);
                std::cout << "\n\n\n\n" << std::endl;
            }
            break;

            case 2 : {
                char ch;

                std::cout << "\nSure to exit? (Y/N): ";
                std::cin >> ch;
                if(tolower(ch) == 'y') {
                    exit(0);
                } else {
                    std::cout << "\n\n\n\n" << std::endl;
                    continue;
                }
            }
            break;
        }
    }
    return 0;
}

void inputNumber(Stack<int>& stk) {
    int d;

    while(true) {
        while(!(std::cin >> d) || !(d >= -1 && d <= 9)) {
            std::cout << "Please enter a valid digit.\n";
            CLEAR_INPUT_BUFFER(std::cin);
        }    
        if(d != -1) {
            if(stk.push(d) == -1) {
                std::cout << "No more digits could be pushed onto the stack.\n";
                break;
            }
        } else {
            break;
        }
    }
    return;
}

Stack<int> addStackNumbers(Stack<int>& stk1, Stack<int>& stk2) {
    unsigned int sum = 0, carry = 0;
    Stack<int> sumstk;

    while(!stk1.isEmpty() && !stk2.isEmpty()) {
        sum = stk1.top() + stk2.top() + carry;
        if(sumstk.push(sum % 10) == -1) {
            std::cout << "\nSum stack overflowed!\nResult may not be correct.\n";
        }
        carry = sum / 10;
        stk1.pop();
        stk2.pop();
    }
    if(stk1.isEmpty()) {
        while(!stk2.isEmpty()) {
            sum = stk2.top() + carry;
            sumstk.push(sum % 10);
            carry = sum / 10;
            stk2.pop();
        }
    } else if(stk2.isEmpty()) {
        while(!stk1.isEmpty()) {
            sum = stk1.top() + carry;
            sumstk.push(sum % 10);
            carry = sum / 10;
            stk1.pop();
        }
    }
    return sumstk;
}

void clearStack(Stack<int>& stk) {
    while(!stk.isEmpty()) {
        stk.pop();
    }
    return;
}