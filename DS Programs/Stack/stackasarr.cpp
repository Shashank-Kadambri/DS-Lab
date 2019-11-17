#include <iostream>
#include <limits>
#include <iomanip>

#define CLEAR_INPUT_BUFFER() \
    std::cin.clear(); \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

template <class T>
class Stack {
    private:
        int tos;
        int size;
        T* arr;
    public:
        Stack() : tos(-1), size(0), arr(NULL) {}
        Stack(const int& size) : tos(-1), size(size) {
            arr = new(std::nothrow) T[size];
        } 
        ~Stack() {
            tos = -1;
            size = 0;
            delete[] arr;
        }

        bool isFull() { return (tos == size - 1); }
        bool isEmpty() { return (tos == -1); }

        int push(const T& val) {
            if(!isFull()) {
                arr[++tos] = val;
                return 0;
            } else {
                return -1;
            }
        }

        int pop() {
            if(!isEmpty()) {
                --tos;
                return 0;
            } else {
                return -1;
            }
        }

        T top() {
            if(!isEmpty()) {
                return arr[tos];
            } else {
                return static_cast<T>(0);
            }
        }
};

int main() {
    int choice, element, n = 0;
    Stack<int> stack;
    do {
        std::cout << "\n\t\tSTACK IMPLEMENTATION USING ARRAY\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Push\n\t\t"
                << "2. Pop\n\t\t"
                << "3. Get top element\n\t\t"
                << "4. Clear\n\t\t"
                << "5. Exit\n\n"
                << "Enter your choice : ";
        while(!(std::cin >> choice) || !(choice >= 1 && choice <= 5)) {
            std::cout << "Please enter a valid choice : ";
            CLEAR_INPUT_BUFFER();
        }
        CLEAR_INPUT_BUFFER();
        switch(choice) {
            case 1 : {
                if(n == 0) {
                    std::cout << "\nEnter the size of the stack : ";
                    while(!(std::cin >> n) || (n < 1)) {
                        std::cout << "Please enter a valid size for the stack : ";
                        CLEAR_INPUT_BUFFER();
                    }
                    CLEAR_INPUT_BUFFER();
                    stack = Stack<int>(n);
                }
                std::cout << "\nEnter the element to be pushed onto the stack : ";
                while(!(std::cin >> element)) {
                    std::cout << "Please enter a valid number : ";
                    CLEAR_INPUT_BUFFER();
                }
                CLEAR_INPUT_BUFFER();
                if(stack.push(element) == -1) {
                    std::cout << "\n*** Stack overflow ***\n";
                } else {
                    std::cout << std::endl << element << " successfully pushed onto the stack!\n";
                }
            } break;

            case 2 : {
                if(stack.pop() == -1) {
                    std::cout << "\n*** Stack underflow ***\n";
                } else {
                    std::cout << "\nStack popped successfully!\n";
                }
            } break;

            case 3 : {
                if((element = stack.top()) == 0) {
                    std::cout << "\n*** Stack is empty ***\n";
                } else {
                    std::cout << "\nTop element of the stack is ---> " << element << std::endl;
                }
            } break;

            case 4 : {
                stack.~Stack();
                std::cout << "\n*** Stack cleared ***\n";
            } break;
        }
        if(choice != 5) {
            std::cout << std::setw(80) << std::setfill('*') << std::endl;
            std::cout << "\n\n\n";
        }
    } while(choice != 5);
    return 0;
}