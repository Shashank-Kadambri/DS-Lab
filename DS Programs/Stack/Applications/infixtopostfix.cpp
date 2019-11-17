#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>
#include "stack.h"

#define CLEAR_INPUT_BUFFER(c) \
    c.clear(); \
    c.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

bool areParenthesesBalanced(std::string&);
std::string infixToPostfix(std::string&);
int operatorPrecedence(char);

int main(void) {
    int choice;

    while(true) {
        std::cout << "\t\tPROGRAM TO CONVERT INFIX EXPRESSION TO POSTFIX\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Enter an infix expression\n\t\t"
                << "2. Exit the program\n\n"
                << "Enter your choice: ";
        while(!(std::cin >> choice) || !(choice == 1 || choice == 2)) {
            CLEAR_INPUT_BUFFER(std::cin);
            std::cout << "Please enter a valid choice: ";
        }
        CLEAR_INPUT_BUFFER(std::cin);
        switch(choice) {
            case 1 : {
                std::string infix_exp = "a+b*(c^d-e)^(f+g*h)-i";
                // std::cout << "\nEnter the infix expression: ";
                // getline(std::cin, infix_exp);
                // std::cout << "Inside case 1\n";
                if(!areParenthesesBalanced(infix_exp)) {
                    std::cout << "\nInfix expression is not valid (Parentheses are not balanced)\n";
                    break;
                } 
                std::string postfix_exp = infixToPostfix(infix_exp);
                std::cout << "\nPostfix expression: " << postfix_exp << std::endl;
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

std::string infixToPostfix(std::string& s) {
    Stack<char> stk;
    std::string postfix_string;
    unsigned int len = s.length();

    postfix_string.clear();
    for(int i = 0; i < len; ++i) {
        if(s[i] == '(') {
            if(stk.push(s[i]) == -1) {
                std::cout << "\n* Stack overflow *\n";
                break;
            } 
        } else if(isalpha(s[i]) || isdigit(s[i])) {
            postfix_string += s[i];
        } else if(s[i] == ')') {
            while(stk.top() != '(') {
                postfix_string += stk.top();
                stk.pop();
            }
            if(stk.top() == '(')
                stk.pop();
        } else {
            while(operatorPrecedence(s[i]) <= operatorPrecedence(stk.top())) {
                postfix_string += stk.top();
                stk.pop();
            }
            stk.push(s[i]);
        }
    }
    while(!stk.isEmpty()) {
        postfix_string += stk.top();
        stk.pop();
    }
    return postfix_string;
}

int operatorPrecedence(char ch) {
    if(ch == '^')
        return 3;
    if(ch == '*' || ch == '/')
        return 2;
    if(ch == '+' || ch == '-')
        return 1;
    return -1;
}
