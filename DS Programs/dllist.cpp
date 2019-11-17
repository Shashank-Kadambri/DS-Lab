#include <iostream>
#include <iomanip>
#include <limits>
#include <new>
#include <cstddef>

#define CLEAR_INPUT_BUFFER(c) \
    c.clear(); \
    c.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

    // DLList(const DLList<T>& other) {}
    // DLList<T>& operator=(const DLList<T>& other) {}
    public:
    DLList() : head(NULL), tail(NULL) {} 

    ~DLList() {
        DLLNode<T>* temp = head;
        while(temp != NULL) {
            DLLNode<T>* nextnode = temp -> next;
            delete temp;
            temp = nextnode;
        }
        head = tail = NULL;
    }

    DLList(const DLList<T>& other) {
        DLLNode<T>* temp = other.head;
        while(temp != NULL) {
            addAtTail(temp -> data);
            temp = temp -> next;
        }
    }

    DLList<T>& operator=(const DLList<T>& list) {
        DLList<T>* ret_list = this;
        DLLNode<T>* temp = list.head;
        while(temp != NULL) {
            ret_list -> addAtTail(temp -> data);
            temp = temp -> next;
        }
    }

    DLList<T> operator+(const DLList<T>& list) {
        std::cout << "\nCALLED\n";
        DLList<T>* ret_list = this;
        DLLNode<T>* temp = list.head;
        while(temp != NULL) {
            ret_list -> addAtTail(temp -> data);
            temp = temp -> next;
        }
        return *ret_list;
    }

    int addAtHead(T data) {
        DLLNode<T>* temp = new(std::nothrow) DLLNode<T>(data);
        if(temp == NULL) {
            return -1;
        }
        if(head == NULL && tail == NULL) {
            head = tail = temp;
        } else {
            temp -> next = head;
            head -> prev = temp;
            head = temp;
        }
        return 0;
    }

    int deleteNthNodeFromTail(long N) {
        if(head == NULL) {
            return -2;
        }
        if(head == tail) {
            if(N == 1) {
                delete tail;
                head = tail = NULL;
            } else {
                return -1;
            }
        } else if(N == 1) {
            tail = tail -> prev;
            delete (tail -> next);
            tail -> next = NULL;
        } else {
            long i = 1;
            DLLNode<T>* temp = tail;
            while(i <= N) {
                temp = temp -> prev;
                ++i;
                if(i == N && temp == head) {
                    head = head -> next;
                    delete (head -> prev);  // or delete temp;
                    head -> prev = NULL;
                    return 0;
                } else if(temp == head) {
                    return -1;
                } else if(i == N) {
                    temp -> prev -> next = temp -> next;
                    temp -> next -> prev = temp -> prev;
                    delete temp;      
                }
            }
        
            // for(i = 0; i < N - 1 && temp != head; ++i) {
            //     temp = temp -> prev;
            // }
            // if(temp == head) {
            //     if(i == N - 1) {
            //         head = head -> next;
            //         delete (head -> prev);
            //         head -> prev = NULL;
            //     } else {
            //         return -1;
            //     }
            // } else {
            //     temp -> prev -> next = temp -> next;
            //     temp -> next -> prev = temp -> prev;
            //     delete temp;
            // }
        }
        return 0;
    }

    int addInMiddle(T data) {
        DLLNode<T>* temp = new(std::nothrow) DLLNode<T>(data);
        if(temp == NULL) {
            return -1;
        }
        if(head == NULL) {
            head = tail = temp;
        } else if(head == tail) {
            temp -> prev = tail;
            tail -> next = temp;
            tail = temp;
        } else {
            DLLNode<T>* slow = head;
            DLLNode<T>* fast = head -> next;
            while(fast && fast -> next) {
                slow = slow -> next;
                fast = fast -> next -> next;
            }
            temp -> prev = slow;
            temp -> next = slow -> next;
            slow -> next -> prev = temp;
            slow -> next = temp;
        }
        return 0;
    }

    int addAtTail(T data) {
        DLLNode<T>* temp = new(std::nothrow) DLLNode<T>(data);
        if(temp == NULL) {
            return -1;
        }
        if(head == NULL && tail == NULL) {
            head = tail = NULL;
        } else {
            temp -> prev = tail;
            tail -> next = temp;
            tail = temp;
        }
        return 0;
    }

    int deleteFromHead() {
        DLLNode<T>* temp = head;
        if(head == NULL && tail == NULL) {
            return -1;
        } 
        if(head == tail) {
            delete head;
            head = tail = NULL;
        } else {
            head = head -> next;
            head -> prev = NULL;
            delete temp;
        }
        return 0;
    }

    int deleteFromTail() {
        DLLNode<T>* temp = tail;
        if(head == NULL && tail == NULL) {
            return -1;
        }
        if(head == tail) {
            delete tail;
            head = tail = NULL;
        } else {
            tail = tail -> prev;
            tail -> next = NULL;
            delete temp;
        }
        return 0;
    }



    void traverseForwards() {
        DLLNode<T>* temp = head;
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

    // int deleteAfterNthNode(int N) {
    //     if(head == NULL && tail == NULL) {
    //         return -2;
    //     }
    //     int index = 1;
    //     DLLNode<T>* temp = head;
    //     // checking if node after nth node exists or not; returns -1 if it doesn't
    //     while(temp != NULL && index < N) {
    //         temp = temp -> next;
    //         ++index;
    //         if(temp == NULL) {
    //             return -1;
    //         }
    //     }
    //     if(temp -> next -> next != NULL) {
    //         DLLNode<T>* tobedeleted = temp -> next;
    //         temp -> next = temp -> next -> next;
    //         temp -> next -> next -> prev = temp;
    //         delete tobedeleted;
    //         std::cout << "\ntemp -> next = " << temp -> next << std::endl;
    //         std::cout << "tail = " << tail << std::endl;
    //         std::cout << "temp = " << temp << std::endl;
    //         std::cout << "tail -> prev = " << tail -> prev << std::endl;
    //         std::cout << "temp -> next -> prev = " << temp -> next -> prev << std::endl;
    //     } else {
    //         deleteFromTail();
    //     }
    //     return 0;
    // }

    

    int deleteNthNode(int N) {
        if(head == NULL && tail == NULL) {
            return -2;
        }
        DLLNode<T>* temp = head;
        int index;
        for(index = 1; temp != NULL && index < N; ++index) {
            temp = temp -> next;
        }
        if(N == 1) {
            deleteFromHead();
        } else if(temp == tail) {
            deleteFromTail();
        } else if(temp != NULL) {
            temp -> prev -> next = temp -> next;
            temp -> next -> prev = temp -> prev;
            delete temp;
        } else {
            return -1;
        }
        return 0;
    }
};

int main() {
    int choice;
    DLList<int> dll;

    do {
        std::cout << "\t\tDOUBLY LINKED LIST DEMO\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Add at head\n\t\t"
                << "2. Add at tail\n\t\t"
                << "3. Delete from head\n\t\t"
                << "4. Delete from tail\n\t\t"
                << "5. Delete Nth node\n\t\t"
                << "6. Traverse forwards\n\t\t"
                << "7. Traverse backwards\n\t\t"
                << "8. Add in the middle\n\t\t"
                << "9. Delete Nth node from the end\n\t\t"
                << "10. Concatenate two lists\n\t\t"
                << "11. Exit the program\n\n"
                << "Enter your choice: ";
        while(!(std::cin >> choice) || !(choice >= 1 && choice <= 11)) {
            std::cout << "Please enter a valid choice: ";
            CLEAR_INPUT_BUFFER(std::cin);
        }
        CLEAR_INPUT_BUFFER(std::cin);

        switch(choice) {
            case 1 : {
                // int value;
                // std::cout << "\nEnter the value to be inserted at the head (any number): ";
                // while(!(std::cin >> value)) {
                //     std::cout << "Please enter a number to be inserted at the head: ";
                //     CLEAR_INPUT_BUFFER(std::cin);
                // }
                // if(dll.addAtHead(value) == -1) {
                //     std::cerr << "\nERROR: Memory could not be allocated\n";
                //     return -1;
                // }
                dll.addAtHead(32);
                dll.addAtHead(59);
                dll.addAtHead(68);
            }
            break;

            case 2 : {
                // int value;
                // std::cout << "\nEnter the value to be inserted at the tail (any number): ";
                // while(!(std::cin >> value)) {
                //     std::cout << "Please enter a number to be inserted at the tail: ";
                //     CLEAR_INPUT_BUFFER(std::cin);
                // }
                // if(dll.addAtTail(value) == -1) {
                //     std::cerr << "\nERROR: Memory could not be allocated\n";
                //     return -1;
                // }
                dll.addAtTail(74);
                dll.addAtTail(86);
            } 
            break;

            case 3 : {
                if(dll.deleteFromHead() == -1) {
                    std::cout << "\nLinked list is empty!";
                }
            }
            break;

            case 4 : {
                if(dll.deleteFromTail() == -1) {
                    std::cout << "\nLinked list is empty!";
                }
            }
            break;

            case 5 : {
                int N;
                std::cout << "\nEnter the value of N: ";
                while(!(std::cin >> N) || (N <= 0)) {
                    std::cout << "Please enter a valid value for N: ";
                    CLEAR_INPUT_BUFFER(std::cin);
                }
                CLEAR_INPUT_BUFFER(std::cin);
                int check = dll.deleteNthNode(N);
                if(check == -2) {
                    std::cout << "\nLinked list is empty!";
                } else if(check == -1) {
                    std::cout << "\nInvalid node position"; 
                } else {
                    std::cout << "\nNode no. " << N << " successfully deleted!";
                }
            }
            break;

            case 6 : {
                std::cout << "\nLinked list (traversing forwards):\n";
                dll.traverseForwards();
            }
            break;

            case 7 : {
                std::cout << "\nLinked list (traversing backwards):\n";
                dll.traverseBackwards();
            }
            break;

            case 8 : {
                int value;
                std::cout << "\nEnter the value to be inserted in the middle (any number): ";
                while(!(std::cin >> value)) {
                    std::cout << "Please enter a number to be inserted in the middle: ";
                    CLEAR_INPUT_BUFFER(std::cin);
                }
                if(dll.addInMiddle(value) == -1) {
                    std::cerr << "\nERROR: Memory could not be allocated\n";
                    return -1;
                }
            }
            break;

            case 9 : {
                long N;
                std::cout << "\nEnter the value of N : ";
                while(!(std::cin >> N) || (N <= 0)) {
                    std::cout << "Please enter a valid value for N : ";
                    CLEAR_INPUT_BUFFER(std::cin);
                }
                CLEAR_INPUT_BUFFER(std::cin);
                int check = dll.deleteNthNodeFromTail(N);
                if(check == -2) {
                    std::cout << "\nList is empty!\n";
                } else if(check == -1) {
                    std::cout << "\nNode could not be located!\n";
                } else if(check == 0) {
                    std::cout << "\nNode deleted successfully!\n";
                }
            }
            break;

            case 10 : {
                DLList<int> list1, list2;
                list1.addAtHead(32);
                list1.addAtTail(14);
                list1.addAtTail(64);
                std::cout << "\nlist1:\n";
                list1.traverseForwards();
                list2.addAtHead(15);
                list2.addAtTail(84);
                list2.addAtTail(69);
                std::cout << "\n\nlist2:\n";
                list2.traverseForwards();
                list1 + list2;
                std::cout << "\n\nlist1:\n";
                list1.traverseForwards();
                std::cout << "\n\nlist2:\n";
                list2.traverseForwards();
            }
        }
        if(choice != 11) {
            std::cout << "\n\n\nPress any key to continue...";
            std::getchar();
            std::cout << "\n" << std::endl;
            std::cout << std::setw(80) << std::setfill('*') << std::endl;
            std::cout << "\n\n";
        }
    } while(choice != 11);
    return 0;
}
