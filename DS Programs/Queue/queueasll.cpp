#include <iostream>
#include <iomanip>
#include <limits>

#define CLEAR_INPUT_BUFFER() \
    std::cin.clear(); \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

template <class T>
class QueueNode {
    public:
    T data;
    QueueNode<T>* next;
    QueueNode() : data(), next(NULL) {}
    QueueNode(const T& data) : data(data), next(NULL) {}
};

template <class T>
class Queue {
    private:
    QueueNode<T>* front;
    QueueNode<T>* rear;
    Queue(const Queue<T>& other) {}
    Queue<T>& operator=(const Queue<T>& other) {}
    public:
    Queue() : front(NULL), rear(NULL) {}
    ~Queue() {
        QueueNode<T>* temp = front;
        while(temp != NULL) {
            QueueNode<T>* nextnode = temp -> next;
            delete temp;
            temp = nextnode;
        }
        front = rear = NULL;
    }

    int enQueue(T data) {
        QueueNode<T>* newnode = new(std::nothrow) QueueNode<T>(data);
        if(newnode == NULL) {
            return -1;
        }
        if(rear == NULL) {
            front = rear = newnode;
        } else {
            rear -> next = newnode;
            rear = newnode;
        }
        return 0;
    }

    int deQueue() {
        if(front == NULL) {
            return -1;
        }
        if(front == rear) {
            delete front;
            front = rear = NULL;
        } else {
            QueueNode<T>* temp = front;
            front = front -> next;
            delete temp;
        }
        return 0;
    }

    void display() {
        QueueNode<T>* temp = front;
        if(front == NULL) {
            std::cout << "\nQueue is empty!\n";
        } else {
            while(temp != NULL) {
                std::cout << temp -> data << "  ";
                temp = temp -> next;
            }
        }
        return;
    }
};

int main() {
    int choice;
    Queue<int> q;

    do {
        std::cout << "\t\tQUEUE USING LINKED LIST DEMO\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Enqueue\n\t\t"
                << "2. Dequeue\n\t\t"
                << "3. Print queue\n\t\t"
                << "4. Exit\n\n"
                << "Enter your choice : ";
        while(!(std::cin >> choice) || !(choice >= 1 && choice <= 4)) {
            std::cout << "Please enter a valid choice : ";
            CLEAR_INPUT_BUFFER();
        }
        CLEAR_INPUT_BUFFER();

        switch(choice) {
            case 1 : {
                int val;
                std::cout << "\nEnter the value to be enqueued : ";
                while(!(std::cin >> val)) {
                    std::cout << "Please enter a valid number : ";
                    CLEAR_INPUT_BUFFER();
                }
                CLEAR_INPUT_BUFFER();
                if(q.enQueue(val) == -1) {
                    std::cerr << "\nERROR: Memory could not be allocated\n";
                    exit(-1);
                } else {
                    std::cout << "\n" << val << " enqueued successfully!\n";
                }
            }
            break;

            case 2 : {
                if(q.deQueue() == -1) {
                    std::cout << "\nQueue is empty!\n";
                } else {
                    std::cout << "\nQueue dequeued successfully!\n";
                }
            }
            break;

            case 3 : {
                std::cout << "\nQueue:\n";
                q.display();
            }
            break;
        }
        if(choice != 4) {
            std::cout << "\n\nPress Enter to continue...";
            CLEAR_INPUT_BUFFER();
            std::cout << "\n\n\n";
            std::cout << std::setw(80) << std::setfill('*') << std::endl;
            std::cout << "\n\n";
        }
    } while(choice != 4);
    return 0;
}