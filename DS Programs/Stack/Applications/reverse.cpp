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
    public:
    DLList() : head(NULL), tail(NULL) {}
    // DLList(const DLList<T>& other) {
    //     std::cout << "\nCOPY CONSTRUCTOR CALLED\n";
    //     head = new(std::nothrow) DLLNode<T>;
    //     tail = new(std::nothrow) DLLNode<T>;
    //     if(head != NULL && tail != NULL) {
    //         head = other.head;
    //         tail = other.tail;
    //     } 
    // }
    // DLList<T>& operator=(const DLList<T>& other) {
    //     std::cout << "\nASSIGNMENT OPERATOR CALLED\n";
    //     head = new(std::nothrow) DLLNode<T>;
    //     tail = new(std::nothrow) DLLNode<T>;
    //     if(head != NULL && tail != NULL) {
    //         head = other.head;
    //         tail = other.tail;
    //     }
    // }

    void destroyList() {
        DLLNode<T>* temp = head;
        while(temp != NULL) {
            DLLNode<T>* nextnode = temp -> next;
            delete temp;
            temp = nextnode; 
        }
        head = tail = NULL;
    }

    ~DLList() {
        destroyList();
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

    DLList<T>& reverseList(const DLList<T>& other) {
        DLLNode<T>* temp = other.tail;
        while(temp != NULL) {
            this -> addAtTail(temp -> data);
            temp = temp -> prev;
        }
        return *this;
    } 
};

void inputNumber(DLList<int>&);

int main() {
    char choice;
    DLList<int> dll;
    DLList<int> revdll;

    do {
        std::cout << "\t\tREVERSE A DOUBLY LINKED LIST DEMO\n\n"
                << "Enter a number digit-by-digit (-1 to terminate): ";
        inputNumber(dll);
        std::cout << "\nEntered number:\n";
        dll.display();
        revdll.reverseList(dll);
        std::cout << "\n\nReversed number:\n";
        revdll.display();
        dll.destroyList();
        revdll.destroyList();
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