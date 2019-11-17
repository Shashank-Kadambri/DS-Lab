#include <iostream>
#include <limits>
#include <iomanip>

#define CLEAR_INPUT_BUFFER() \
    std::cin.clear(); \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

long pow(long b, int r) {
    if(r == 0)
        return 1;
    return b * pow(b, r - 1);
}

int main() {
    int choice;
    do {
        std::cout << "\t\tPROGRAM TO COMPUTE b^r USING RECURSION\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Compute\n\t\t"
                << "2. Exit\n\n"
                << "Enter your choice : ";
        while(!(std::cin >> choice) || !(choice == 1 || choice == 2)) {
            std::cout << "Please enter a valid choice : ";
            CLEAR_INPUT_BUFFER();
        }
        CLEAR_INPUT_BUFFER();
        if(choice != 2) {
            int b, r;
            std::cout << "\nEnter the base (b) : ";
            while(!(std::cin >> b)) {
                std::cout << "Please enter a valid number : ";
                CLEAR_INPUT_BUFFER();
            }
            CLEAR_INPUT_BUFFER();
            std::cout << "Enter the power (r) : ";
            while(!(std::cin >> r)) {
                std::cout << "Please enter a valid number : ";
                CLEAR_INPUT_BUFFER();
            }
            CLEAR_INPUT_BUFFER();
            std::cout << "\n\nAnswer : " << b << "^" << r << " = " << pow(b, r);
            std::cout << std::setw(80) << std::setfill('*') << std::endl;
            std::cout << "\n\n\n";
        }
    } while(choice != 2);
    return 0;
}