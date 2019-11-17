#include <iostream>
#include <iomanip>
#include <limits>

#define MAX 10
#define CLEAR_INPUT_BUFFER() \
    std::cin.clear(); \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

template <class T>
class CQueue {
    private:
        T* arr;
        int front, rear, size;
    public:
        CQueue() : arr(NULL), front(-1), rear(-1), size(0) {}
        CQueue(int size) : front(-1), rear(-1), size(size) {
            arr = new T[size];
        }
        ~CQueue() {
            destroyQueue();
        }

        void initializeSize(int size) {
            size = size;
            arr = new T[size];
            front = rear = -1;
        }

        // bool isEmpty() {
        //     return (front == -1 && rear == -1);
        // }

        // bool isFull() {
        //     return ((rear + 1) % size == front);
        // }

        int enQueue(T val) {
            if((rear + 1) % size == front) {
                return -1;
            } else {
                if(front == -1)
                    front = 0;
                rear = (rear + 1) % size;
                arr[rear] = val;
                return 0;
            } 
        }

        int deQueue() {
            if(front == -1 && rear == -1) {
                return -1;
            } else if(front == rear) {
                front = rear = -1;
            } else {
                front = (front + 1) % size;
            }
            return 0;
        }

        void displayQueue() {
            if(front == -1 && rear == -1) {
                std::cout << "\n*** Queue is empty! ***\n";
            } else if(front <= rear) {
                for(int i = front; i <= rear; ++i) {
                    std::cout << arr[i] << "  ";
                }
            } else {
                for(int i = front; i < size; ++i) {
                    std::cout << arr[i] << "  ";
                }
                for(int i = 0; i <= rear; ++i) {
                    std::cout << arr[i] << "  ";
                }
            }
            return;
        }

        void destroyQueue() {
            delete[] arr;
        }
};

int main() {
    CQueue<int> cqueue(MAX);
    int choice, size = MAX;
    int flag = 0;
    do {
        std::cout << "\n\t\tQUEUE USING CIRCULAR ARRAY\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Enqueue\n\t\t"
                << "2. Dequeue\n\t\t"
                << "3. Display queue\n\t\t"
                << "4. Exit\n\n"
                << "Enter your choice : ";
        while(!(std::cin >> choice) || !(choice >= 1 && choice <= 4)) {
            std::cout << "Please enter a valid choice : ";
            CLEAR_INPUT_BUFFER();
        }
        CLEAR_INPUT_BUFFER();
        if(choice == 1 && flag == 0) {
            std::cout << "Enter the size of the queue : ";
            while(!(std::cin >> size) || (size < 1)) {
                std::cout << "Please enter a valid size : ";
                CLEAR_INPUT_BUFFER();
            }
            CLEAR_INPUT_BUFFER();
            cqueue.initializeSize(size);
            flag = 1;
        }
        switch(choice) {
            case 1 : {
                int val;
                std::cout << "\nEnter the value to be enqueued : ";
                while(!(std::cin >> val)) {
                    std::cout << "Please enter a valid number : ";
                    CLEAR_INPUT_BUFFER();
                }
                CLEAR_INPUT_BUFFER();
                if(cqueue.enQueue(val) == -1) {
                    std::cout << "\n\n*** Queue is full! ***\n";
                } else {
                    std::cout << "\n\n" << val << " enqueued\n";
                }
            } break;

            case 2 : {
                if(cqueue.deQueue() == -1) {
                    std::cout << "\n\n*** Queue is empty! ***\n";
                } else {
                    std::cout << "\n\nQueue dequeued\n";
                }
            } break;

            case 3 : {
                std::cout << "\n\nQueue:\n";
                cqueue.displayQueue();
            } break;
        }
        if(choice != 4) {
            std::cout << std::setw(80) << std::setfill('*') << std::endl;
            std::cout << "\n\n\n";
        }
    } while(choice != 4);
    // cqueue.destroyQueue();
    return 0;
}