#include <iostream>
#include <limits>
#include <iomanip>

#define CLEAR_INPUT_BUFFER() \
    std::cin.clear(); \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

template <class T>
class DLLNode {
    public:
    T data;
    DLLNode<T>* next;
    DLLNode<T>* prev;
    DLLNode() : data(), next(NULL), prev(NULL) {}
    DLLNode(const T& data) : data(data), next(NULL), prev(NULL) {}
};

template <class T>
class DLList {
    private:
    DLLNode<T>* head;
    DLLNode<T>* tail;
    DLList(const DLList<T>& other) {}
    DLList<T>& operator=(const DLList<T>& other) {}
    public:
    DLList() : head(NULL), tail(NULL) {}
    ~DLList() {
        destroyList();
    }

    void destroyList() {
        DLLNode<T>* temp = head;
        while(temp != NULL) {
            DLLNode<T>* nextnode = temp -> next;
            delete temp;
            temp = nextnode;
        }
        head = tail = NULL;
    }

    int addAtTail(T data) {
        DLLNode<T>* newnode = new(std::nothrow) DLLNode<T>(data);
        if(newnode == NULL) {
            return -1;
        }
        if(head == NULL) {
            head = tail = newnode;
        } else {
            newnode -> prev = tail;
            tail -> next = newnode;
            tail = newnode;
        }
        return 0;
    }

    void display() {
        DLLNode<T>* temp = head;
        if(head == NULL) {
            std::cout << "\nNo number entered!\n";
            return;
        }
        while(temp != NULL) {
            std::cout << temp -> data;
            temp = temp -> next;
        }
        return;
    }

    bool isPalindrome() {
        DLLNode<T>* forward = head;
        DLLNode<T>* backward = tail;
        if(head == NULL) {
            return false;
        }
        int flag = 1; 
        // first condition needs to be checked in cases where number of digits is odd
        // second condition needs to be checked in cases where number of digits is even
        while(!(forward == backward) && !(forward -> prev == backward)) {
            if(forward -> data == backward -> data) {
                forward = forward -> next;
                backward = backward -> prev;
            } else {
                flag = 0;
                break;
            }
        }
        return flag;
    }
};

void inputNumber(DLList<int>&);

int main() {
    char choice;
    DLList<int> dll;

    do {
        std::cout << "\t\tCHECK PALINDROME USING DOUBLY LINKED LIST\n\n"
                << "Please enter a number digit-by-digit (-1 to terminate): ";
        inputNumber(dll);
        std::cout << "\nEntered number:\n";
        dll.display();
        if(dll.isPalindrome()) {
            std::cout << "\nThe entered number is palindrome.";
        } else {
            std::cout << "\nThe entered number is not palindrome.";
        }
        dll.destroyList();
        std::cout << "\n\n\nDo you wish to continue? (Y/N): ";
        std::cin >> choice;
        std::cout << "\n\n";
        std::cout << std::setw(80) << std::setfill('*') << std::endl;
        std::cout << "\n\n";
    } while(tolower(choice) == 'y');
    return 0;
}

void inputNumber(DLList<int>& list) {
    int digit;
    while(true) {
        while(!(std::cin >> digit) || !(digit >= -1 && digit <= 9)) {
            std::cout << "Please enter a valid digit : ";
            CLEAR_INPUT_BUFFER();
        }
        CLEAR_INPUT_BUFFER();
        if(digit != -1) {
            if(list.addAtTail(digit) == -1) {
                std::cerr << "\nERROR: Memory could not be allocated\n";
                exit(-1);
            }
        } else {
            break;
        }
    }
    return;
}