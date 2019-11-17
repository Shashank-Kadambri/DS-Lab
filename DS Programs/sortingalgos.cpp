#include <iostream>
#include <iomanip>
#include <limits>

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

/*
    Set swap counter to 0.
    If two adjacent elements are not in order, swap them and increment the swap counter by 1.
    If swap counter remains 0, the array is sorted; else reset swap counter to 0 for next pass.
*/
template <typename T>
void bubbleSort(T arr[], int size) {
    int swap_counter = 0;
    int no_of_comparisons = 0;
    for(int i = 0; i < size - 1; ++i) {
        for(int j = 0; j < size - i - 1; ++j) {
            if(arr[j] > arr [j+1]) {
                 ++no_of_comparisons;
                std::swap(arr[j], arr[j+1]);
                ++swap_counter;
            }
        } 
        if(swap_counter == 0) {
            std::cout << "\nTotal number of comparisons = " << no_of_comparisons << std::endl;
            return;
        }
        else
            swap_counter = 0;
    }
    std::cout << "\nTotal number of comparisons = " << no_of_comparisons << std::endl;
    return;
}

/*
    Repeat until no unsorted elements remain:
        Search the unsorted portion for the smallest element.
        Swap it with the first element in the unsorted portion.
*/
template <typename T>
void selectionSort(T arr[], int size) {
    int no_of_comparisons = 0;
    for(int i = 0; i < size - 1; ++i) {
        int min = i;
        for(int j = i + 1; j < size; ++j) {
            ++no_of_comparisons;
            if(arr[j] < arr[min]) {
                min = j;
            }
        }
        std::swap(arr[i], arr[min]);
    }
    std::cout << "\nTotal number of comparisons = " << no_of_comparisons << std::endl;
    return;
}

/*
    Call the first element of the array "sorted".
    Repeat until all elements are sorted:
        Look at the next unsorted element. Insert into the "sorted" portion by shifting the requisite number of elements.
*/
template <typename T>
void insertionSort(T arr[], int size) {
    int no_of_comparisons = 0;
    for(int i = 1; i < size; ++i) {
        int temp = arr[i];
        int hole = i;
        while(hole > 0 && arr[hole-1] > temp) {
            ++no_of_comparisons;
            arr[hole] = arr[hole-1];
            --hole;
        }
        arr[hole] = temp;
    }
    std::cout << "\nTotal number of comparisons = " << no_of_comparisons << std::endl;
    return;
}

template <typename T>
void merge(T arr[], int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;
    int leftarr[n1];
    int rightarr[n2];
    int i, j, k;
    
    // populating the left and right sub-arrays
    for(i = 0; i < n1; ++i) {
        leftarr[i] = arr[start + i];
    }
    for(j = 0; j < n2; ++j) {
        rightarr[j] = arr[mid + 1 + j];
    }

    i = j = 0;
    k = start;
    while(i < n1 && j < n2) {
        if(leftarr[i] < rightarr[j]) {
            arr[k++] = leftarr[i++];
        } else {
            arr[k++] = rightarr[j++];
        }
    }
    while(i < n1) {
        arr[k++] = leftarr[i++];
    }
    while(j < n2) {
        arr[k++] = rightarr[j++];
    }
}

template <typename T>
void mergeSort(T arr[], int start, int end) {
    if(start < end) {
        int mid = (start + end) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
    return;
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

template <typename T>
int partition(T arr[], int start, int end) {
    int pivot = arr[end];   // the last element is chosen as pivot
    int i = start - 1;

    // if any element is smaller than the pivot element, then increment i,
    // and swap elements at ith and jth indices 
    for(int j = start; j < end; ++j) {
        if(arr[j] < pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    // place the pivot element at (i+1)th index, in its sorted position
    swap(arr[i + 1], arr[end]);
    return i + 1;
}

/*
    Choose an element to be the pivot element, and then parition the array
    such that all the elements to the left of the pivot element are smaller than it, and
    all the elements to the right of the pivot element are larger than it.
    Perform this recursively.
*/
template <typename T>
void quickSort(T arr[], int start, int end) {
    if(start < end) {
        int pivotindex = partition(arr, start, end);
        quickSort(arr, start, pivotindex - 1);
        quickSort(arr, pivotindex + 1, end);
    }
    return;
}

int main() {
    int choice, n;
    int* arr;
    do {
        std::cout << "\t\tPROGRAM TO DEMONSTRATE SORTING ALGORITHMS\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Bubble Sort\n\t\t"
                << "2. Selection Sort\n\t\t"
                << "3. Insertion Sort\n\t\t"
                << "4. Merge Sort\n\t\t"
                << "5. Quick sort\n\t\t"
                << "6. Exit\n\n"
                << "Enter your choice : ";
        while(!(std::cin >> choice) || !(choice >= 1 && choice <= 6)) {
            std::cout << "Please enter a valid choice : ";
            CLEAR_INPUT_BUFFER();
        }
        CLEAR_INPUT_BUFFER();

        if(choice != 6) {
            std::cout << "\nHow many elements do you want to enter? : ";
            while(!(std::cin >> n)) {
                std::cout << "Please enter a valid number : ";
                CLEAR_INPUT_BUFFER();
            }
            CLEAR_INPUT_BUFFER();
            std::cout << "\nEnter the elements:\n";
            arr = new int[n];
            getItems(arr, n);
        }

        switch(choice) {
            case 1 : {
                std::cout << "\n\nInput array:\n";
                printItems(arr, n);
                bubbleSort(arr, n);
                std::cout << "\n\nSorted array:\n";
                printItems(arr, n);
            }
            break;

            case 2 : {
                std::cout << "\n\nInput array:\n";
                printItems(arr, n);
                selectionSort(arr, n);
                std::cout << "\n\nSorted array:\n";
                printItems(arr, n);
            }
            break;

            case 3 : {
                std::cout << "\n\nInput array:\n";
                printItems(arr, n);
                insertionSort(arr, n);
                std::cout << "\n\nSorted array:\n";
                printItems(arr, n);
            }
            break;

            case 4 : {
                std::cout << "\n\nInput array:\n";
                printItems(arr, n);
                mergeSort(arr, 0, n - 1);
                std::cout << "\n\nSorted array:\n";
                printItems(arr, n);
            } break;

            case 5 : {
                std::cout << "\n\nInput array:\n";
                printItems(arr, n);
                quickSort(arr, 0, n - 1);
                std::cout << "\n\nSorted array:\n";
                printItems(arr, n);
            } break;
        }
        if(choice != 6) {
            std::cout << std::setw(80) << std::setfill('*') << std::endl;
            std::cout << "\n\n\n\n";
            std::cout << std::endl;
        }
    } while(choice != 6);
    return 0;
}
