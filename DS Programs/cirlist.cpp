#include <iostream>
#include <limits>
#include <iomanip>

#define CLEAR_INPUT_BUFFER() \
    std::cin.clear(); \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

template <class T>
class CLLNode {
    public:
    T data;
    CLLNode<T>* next;
    CLLNode<T>* prev;

    CLLNode() : data(), next(NULL), prev(NULL) {}
    CLLNode(const T& data) : data(data), next(NULL), prev(NULL) {}
};

template <class T>
class CLList {
    private:
    CLLNode<T>* head;

    CLList(const CLList<T>& other) {}
    CLList<T>& operator=(const CLList<T>& other) {}
    public:
    CLList() : head(NULL) {}
    ~CLList() {
        CLLNode<T>* temp = head;
        do {
            CLLNode<T>* nextnode = temp -> next;
            delete temp;
            temp = nextnode;
        } while(temp != head);
        head = NULL;
    }

    int addAtBeginning(T data) {
        CLLNode<T>* temp = new(std::nothrow) CLLNode<T>(data);
        if(temp == NULL) {
            return -1;
        }
        if(head == NULL) {
            temp -> next = temp -> prev = temp;
            head = temp;
        } else {
            temp -> next = head;
            temp -> prev = head -> prev;
            // if only one node is present
            if(head -> next == head && head -> prev == head) {
                head -> next = temp;
            } else {
                head -> prev -> next = temp;
            }
            head -> prev = temp;
            head = temp;
        }
        return 0;
    }

    int addAtEnd(T data) {
        CLLNode<T>* temp = new(std::nothrow) CLLNode<T>(data);
        if(temp == NULL) {
            return -1;
        }
        if(head == NULL) {
            temp -> next = temp -> prev = temp;
            head = temp;
        } else {
            temp -> next = head;
            temp -> prev = head -> prev;
            if(head -> next == head && head -> prev == head) {
                head -> next = temp;
            } else {
                head -> prev -> next = temp;
            }
            head -> prev = temp;
        }
        return 0;
    }

    void traverse() {
        if(head == NULL) {
            std::cout << "\nNo node is present in the list!\n";
            return;    
        }
        CLLNode<T>* temp = head;
        // while(temp -> next != head) {
        //     // std::cout << "\nYO\n";
        //     std::cout << temp -> data << "  ";
        //     temp = temp -> next;
        // }
        do {
            std::cout << temp -> data << "  ";
            temp = temp -> next;
        } while(temp != head);
        return;
    }
};

int main() {
    CLList<int> cll;
    cll.addAtBeginning(59);
    cll.addAtBeginning(32);
    cll.addAtBeginning(64);
    cll.addAtBeginning(89);
    cll.addAtBeginning(76);
    std::cout << std::endl << "\nList:\n";
    cll.traverse();
    std::cout << std::endl;
    cll.addAtEnd(1);
    cll.addAtEnd(2);
    cll.addAtEnd(3);
    std::cout << "List:\n";
    cll.traverse();
}