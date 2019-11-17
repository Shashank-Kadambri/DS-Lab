#include <iostream>
#include <limits>
#include <iomanip>
#include <cstring>

#define CLEAR_INPUT_BUFFER() \
    std::cin.clear(); \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

void reverse(std::string str) {
    if(str.size() == 0) 
        return;
    reverse(str.substr(1));
    std::cout << str[0];
}

int main() {
    int choice;
    do {
        std::cout << "\t\tPROGRAM TO REVERSE A STRING USING RECURSION\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Enter a string\n\t\t"
                << "2. Exit\n\n"
                << "Enter your choice : ";
        while(!(std::cin >> choice) || !(choice == 1 || choice == 2)) {
            std::cout << "Please enter a valid choice : ";
            CLEAR_INPUT_BUFFER();
        }
        CLEAR_INPUT_BUFFER();
        if(choice != 2) {
            std::string str;
            std::cout << "\nEnter the string : ";
            std::getline(std::cin, str);
            std::cout << "\n\nReversed string:\n";
            reverse(str);
            std::cout << std::setw(80) << std::setfill('*') << std::endl;
            std::cout << "\n\n\n";
        }
    } while(choice != 2);
    return 0;
}