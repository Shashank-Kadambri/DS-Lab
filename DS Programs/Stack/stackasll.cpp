#include <iostream>
#include <limits>
#include <iomanip>

#define CLEAR_INPUT_BUFFER() \
    std::cin.clear(); \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

template <class T>
class StackNode {
    public:
    T data;
    StackNode<T>* next;
    StackNode() : data(), next(NULL) {}
    StackNode(const T& data) : data(data), next(NULL) {}
};

template <class T>
class Stack {
    private:
    StackNode<T>* head;
    Stack(const Stack<T>& other) {}
    Stack<T>& operator=(const Stack<T>& other) {}
    public:
    Stack() : head(NULL) {}
    ~Stack() {
        StackNode<T>* temp = head;
        while(temp != NULL) {
            StackNode<T>* nextnode = temp -> next;
            delete temp;
            temp = nextnode;
        }
        head = NULL;
    }

    int push(T data) {
        StackNode<T>* newnode = new(std::nothrow) StackNode<T>(data);
        if(newnode == NULL) {
            return -1;
        }
        if(head == NULL) {
            head = newnode;
        } else {
            newnode -> next = head;
            head = newnode;
        }
        return 0;
    }

    int pop() {
        if(head == NULL) {
            return -1; 
        }
        if(head -> next == NULL) {
            delete head;
            head = NULL;
        } else {
            StackNode<T>* temp = head;
            head = head -> next;
            delete temp;
        }
        return 0;
    }

    T top() {
        if(head == NULL) {
            return static_cast<T>(NULL);
        } else {
            return head -> data;
        }
    }

    void display() {
        StackNode<T>* temp = head;
        if(head == NULL) {
            std::cout << "\nStack is empty!\n";
            return;
        } else {
            while(temp != NULL) {
                std::cout << temp -> data << std::endl;
                temp = temp -> next;
            }
        }
        return;
    }
};

int main() {
    int choice;
    Stack<int> stk;

    do {
        std::cout << "\t\tSTACK USING LINKED LIST DEMO\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Push\n\t\t"
                << "2. Pop\n\t\t"
                << "3. Get top element\n\t\t"
                << "4. Print stack\n\t\t"
                << "5. Exit the program\n\n"
                << "Enter your choice : ";
        while(!(std::cin >> choice) || !(choice >= 1 && choice <= 5)) {
            std::cout << "Please enter a valid choice : ";
            CLEAR_INPUT_BUFFER();
        }
        CLEAR_INPUT_BUFFER();

        switch(choice) {
            case 1 : {
                int val;
                std::cout << "\nEnter the value to be pushed onto the stack : ";
                while(!(std::cin >> val)) {
                    std::cout << "Please enter a valid number : ";
                    CLEAR_INPUT_BUFFER();
                }
                CLEAR_INPUT_BUFFER();
                if(stk.push(val) == -1) {
                    std::cerr << "\nERROR: Memory could not be allocated\n";
                    exit(-1);
                } else {
                    std::cout << "\n" << val << " successfully pushed!\n";
                }
            }
            break;

            case 2 : {
                if(stk.pop() == -1) {
                    std::cout << "\nUNDERFLOW: Stack is empty\n";
                } else {
                    std::cout << "\nStack popped!\n";
                }
            }
            break;

            case 3 : {
                int t = stk.top();
                if(t == 0) {
                    std::cout << "\nStack is empty!\n";
                } else {
                    std::cout << "\nTop element of the stack is -> " << t << "\n";
                }
            }
            break;

            case 4 : {
                std::cout << "\nStack:\n";
                stk.display();
            }
            break;
        }
        if(choice != 5) {
            std::cout << "\n\nPress Enter to continue...";
            CLEAR_INPUT_BUFFER();
            std::cout << "\n\n\n";
            std::cout << std::setw(80) << std::setfill('*') << std::endl;
            std::cout << "\n\n";
        }
    } while(choice != 5);
    return 0;
}