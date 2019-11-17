#include <iostream>
#include <iomanip>
#include <new>
#include <limits>
#include <cstddef>

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
        DLLNode<T>* temp = head;
        while(temp != NULL) {
            DLLNode<T>* tobedeleted = temp;
            temp = temp -> next;
            delete tobedeleted;
        }
        head = tail = NULL;
    } 

    int sortedAdd(T data) {
        DLLNode<T>* temp = new(std::nothrow) DLLNode<T>(data);
        if(temp == NULL) {
            return -1;
        }
        // if list is empty
        if(head == NULL) {
            head = tail = temp;
        } else {
            // add at head
            if(data < head -> data) {
                temp -> next = head;
                head -> prev = temp;
                head = temp;
            } else {
                // move ptr till it reaches the 2nd last node or the data value lies within certain range
                DLLNode<T>* ptr = head;
                while((ptr -> next != NULL) && !((data < ptr -> next -> data) && (data >= ptr -> data))) {
                    ptr = ptr -> next;
                }
                // inserting at tail
                if(ptr -> next == NULL) {
                    temp -> prev = tail;
                    tail -> next = temp;
                    tail = temp;
                } else {
                    // inserting between 2 nodes
                    temp -> next = ptr -> next;
                    temp -> prev = ptr;
                    ptr -> next -> prev = temp;
                    ptr -> next = temp;
                }
            }
        }
        return 0;
    }

    DLLNode<T>* searchInSortedList(T value, int& index) {
        DLLNode<T>* temp = head;
        while(temp != NULL) {
            if(temp -> data == value) {
                return temp;
            } else {
                temp = temp -> next;
                ++index;
            }
        }
        return NULL;
    }

    void merge(const DLList<T>& list1, const DLList<T>& list2) {
        DLLNode<T>* head1 = list1.head;
        DLLNode<T>* head2 = list2.head;
        while(head1 != NULL && head2 != NULL) {
            if(head1 -> data < head2 -> data) {
                sortedAdd(head1 -> data);
                head1 = head1 -> next;
            } else {
                sortedAdd(head2 -> data);
                head2 = head2 -> next;
            }
        }
        if(head1 == NULL) {
            while(head2 != NULL) {
                sortedAdd(head2 -> data);
                head2 = head2 -> data;
            }
        } else {
            while(head1 != NULL) {
                sortedAdd(head1 -> data);
                head1 = head1 -> data;
            }
        }
        return;
    }

    int deleteByValue(T value) {
        if(head == NULL) {
            return -2;
        }
        if((value < head -> data) || (value > tail -> data)) {
            return -1;
        }
        if(head -> data == value) {
            if(head == tail) {
                delete head;
                head = tail = NULL;
            } else {
                // delete from head
                head = head -> next;
                delete (head -> prev);
                head -> prev = NULL;
            }
        } else {
            DLLNode<T>* ptr = head;
            while((ptr -> next != NULL) && (ptr -> data <= value)) {
                if(ptr -> data == value) {
                    break;
                } else {
                    ptr = ptr -> next;
                }
            }
            if((ptr -> next == NULL) && (tail -> data == value)) {
                tail = tail -> prev;
                delete (tail -> next);
                tail -> next = NULL;
            } else if((ptr -> next == NULL) && (tail -> data != value)) {
                return -1;
            } else if(ptr -> data == value) {
                ptr -> prev -> next = ptr -> next;
                ptr -> next -> prev = ptr -> prev;
                delete ptr;
            } else {
                return -1;
            }
        }
        return 0;
    }

    void traverseForwards() {
        DLLNode<T>* temp = head;
        std::cout << "\nIN TRAVERSE FORWARDS\n";
        std::cout << "tail -> next = " << tail -> next <<std::endl;
        if(head == NULL && tail == NULL) {
            std::cout << "\nNo node present in the linked list.";
            return;
        }
        while(temp != NULL) {
            std::cout << temp -> data << "  ";
            temp = temp -> next;
        }
        return;
    }

    void traverseBackwards() {
        DLLNode<T>* temp = tail;
        if(head == NULL && tail == NULL) {
            std::cout << "\nNo node present in the linked list.";
            return;
        }
        while(temp != NULL) {
            std::cout << temp -> data << "  ";
            temp = temp -> prev;
        }
        return;
    }
};

int main() {
    int choice;
    DLList<int> dll;

    do {
        std::cout << "\t\tSORTED DOUBLY LINKED LIST DEMO\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Add a node\n\t\t"
                << "2. Traverse forwards\n\t\t"
                << "3. Traverse backwards\n\t\t"
                << "4. Search by value\n\t\t"
                << "5. Delete by value\n\t\t"
                << "6. Merge two linked lists\n\t\t"
                << "7. Exit the program\n\n"
                << "Enter your choice: ";
        while(!(std::cin >> choice) || !(choice >= 1 && choice <= 7)) {
            std::cout << "Please enter a valid choice: ";
            CLEAR_INPUT_BUFFER();
        }
        CLEAR_INPUT_BUFFER();

        switch(choice) {
            case 1 : {
                // int value;
                // std::cout << "Enter the value to be added in the list: ";
                // while(!(std::cin >> value)) {
                //     std::cout << "Please enter a valid number: ";
                //     CLEAR_INPUT_BUFFER();
                // }
                // CLEAR_INPUT_BUFFER();
                // if(dll.add(value) == -1) {
                //     std::cerr << "\nERROR: Memory could not be allocated\n";
                //     return -1;
                // }
                dll.sortedAdd(68);
                dll.sortedAdd(59);
                dll.sortedAdd(32);
                dll.sortedAdd(74);
                dll.sortedAdd(86);
            }
            break;

            case 2 : {
                std::cout << "\nLinked list (traversing forwards):\n";
                dll.traverseForwards();
            }
            break;

            case 3 : {
                std::cout << "\nLinked list (traversing backwards):\n";
                dll.traverseBackwards();
            }
            break;

            case 4 : {
                int index = 1;
                int value;
                std::cout << "\nEnter the value to be searched in the list: ";
                while(!(std::cin >> value)) {
                    std::cout << "Please enter a valid number to be searched: ";
                    CLEAR_INPUT_BUFFER();
                }
                CLEAR_INPUT_BUFFER();
                if(dll.searchInSortedList(value, index) != NULL) {
                    std::cout << "\n" << value << " was found at node no. " << index << " of the list.";
                } else {
                    std::cout << "\nValue not found!";
                }
            }
            break;

            case 5 : {
                int value;
                std::cout << "\nEnter the value to be deleted from the list: ";
                while(!(std::cin >> value)) {
                    std::cout << "Please enter a valid number: ";
                    CLEAR_INPUT_BUFFER();
                }
                CLEAR_INPUT_BUFFER();
                int check = dll.deleteByValue(value);
                if(check == 0) {
                    std::cout << "\n" << value << " successfully deleted from the list.";
                } else if(check == -1) {
                    std::cout << "\nValue not found!";
                } else if(check == -2) {
                    std::cout << "\nList is empty!";
                }
            }
            break;

            case 6 : {
                // code
            }
        }
        if(choice != 7) {
            std::cout << "\n\n\nPress any key to continue...";
            std::getchar();
            std::cout << "\n" << std::endl;
            std::cout << std::setw(80) << std::setfill('*') << std::endl;
            std::cout << "\n\n";
        }
    } while(choice != 7);
    return 0;
}