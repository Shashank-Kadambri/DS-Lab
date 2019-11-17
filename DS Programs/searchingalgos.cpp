#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>

#define CLEAR_INPUT_BUFFER() \
    std::cin.clear(); \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

template <typename T>
void getItems(T arr[], int n) {
    for(int i = 0; i < n; ++i) {
        while(!(std::cin >> arr[i])) {
            std::cout << "Please enter a valid number : ";
            CLEAR_INPUT_BUFFER();
        }
        CLEAR_INPUT_BUFFER();
    }
    return;
}

template <typename T>
void printItems(T arr[], int n) {
    for(int i = 0; i < n; ++i) {
        std::cout << arr[i] << "  ";
    }
    return;
}

template <typename T>
int linearSearch(T arr[], int size, T x) {
    std::cout << "\nArray:\n";
    printItems(arr, size);
    for(int i = 0; i < size; ++i) {
        if(arr[i] == x)
            return i;
    }
    return -1;
}

template <typename T>
int binarySearch(T arr[], int size, T x) {
    int start = 0;
    int end = size - 1;
    int mid = 0;
    std::sort(arr, arr + size);
    std::cout << "\nSorted array:\n";
    printItems(arr, size); 
    while(start <= end) {
        mid = (start + end) / 2;
        if(x == arr[mid]) {
            return mid;
        } else if(x < arr[mid]) {
            end = mid - 1;
        } else if(x > arr[mid]) {
            start = mid + 1;
        }
    }
    return -1;
}

int main() {
    int choice, n, x;
    int* arr;
    do {
        std::cout << "\t\tPROGRAM TO DEMONSTRATE SEARCHING ALGORITHMS\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Linear Search\n\t\t"
                << "2. Binary Search\n\t\t"
                << "3. Exit\n\n"
                << "Enter your choice : ";
        while(!(std::cin >> choice) || !(choice >= 1 && choice <= 3)) {
            std::cout << "Please enter a valid choice : ";
            CLEAR_INPUT_BUFFER();
        }
        CLEAR_INPUT_BUFFER();

        if(choice != 3) {
            std::cout << "\nEnter the number of elements : ";
            while(!(std::cin >> n)) {
                std::cout << "Please enter a valid number : ";
                CLEAR_INPUT_BUFFER();
            }
            CLEAR_INPUT_BUFFER();
            arr = new int[n];
            std::cout << "\nEnter the elements:\n";
            getItems(arr, n);
            std::cout << "\nEnter the element to be searched in the array : ";
            while(!(std::cin >> x)) {
                std::cout << "Please enter a valid number : ";
                CLEAR_INPUT_BUFFER();
            }
        }

        switch(choice) {
            case 1 : {
                int retval = linearSearch(arr, n, x);
                if(retval == -1) {
                    std::cout << "\n\nElement " << x << " not found in the array";
                } else {
                    std::cout << "\n\nElement " << x << " found at index " << retval;
                }
            }
            break;

            case 2 : {
                int retval = binarySearch(arr, n, x);
                if(retval == -1) {
                    std::cout << "\n\nElement " << x << " not found in the array";
                } else {
                    std::cout << "\n\nElement " << x << " found at index " << retval;
                }
            }
            break;
        }
        if(choice != 3) {
            std::cout << std::setw(80) << std::setfill('*') << std::endl;
            std::cout << "\n\n\n\n" << std::endl;
        }
    } while(choice != 3);
    return 0;
}