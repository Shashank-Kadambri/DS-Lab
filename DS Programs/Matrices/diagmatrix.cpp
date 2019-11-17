#include <iostream>
#include <iomanip>
#include <limits>

#define CLEAR_INPUT_BUFFER() \
    std::cin.clear(); \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

template <class T>
class DiagonalMatrix {
    private:
        int n;
        T* arr;
    public:
        DiagonalMatrix() : n(0), arr(NULL) {}
        DiagonalMatrix(const int& n) : n(n) {
            arr = new(std::nothrow) T[n];
        }
        ~DiagonalMatrix() {
            delete[] arr;
        }

        int store(const int& i, const int& j, const T& val) {
            if(i < 1 || j < 1 || i > n || j > n) {
                return __INT_MAX__;
            }
            if(i == j) {
                arr[i - 1] = val;
            } else {
                // don't know what to do
            }
            return 0;
        }

        T retrieve(const int& i, const int& j) const {
            if(i < 1 || j < 1 || i > n || j > n) {
                std::cout << "\n*** Illegal index reference ***\n";
                return __INT_MAX__;
            } 
            if(i == j) {
                return arr[i - 1];
            } else {
                return 0;
            }
        }

        void print() {
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < n; ++j) {
                    if(i == j) {
                        std::cout << arr[i] << "  ";
                    } else {
                        std::cout << 0 << "  ";
                    }
                }
                std::cout << std::endl;
            }
            return;
        }
};

int main() {
    int dim, choice, element, i, j;
    std::cout << "\n\t\t*** DIAGONAL MATRIX ***\n\nEnter the dimension : ";
    while(!(std::cin >> dim) || (dim < 1)) {
        std::cout << "Please enter a valid dimension : ";
        CLEAR_INPUT_BUFFER();
    }
    CLEAR_INPUT_BUFFER();
    DiagonalMatrix<int> mat(dim);
    do {
        std::cout << "\n\t\tDIAGONAL MATRIX\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Store\n\t\t"
                << "2. Retrieve\n\t\t"
                << "3. Print\n\t\t"
                << "4. Exit\n\n"
                << "Enter your choice : ";
        while(!(std::cin >> choice) || !(choice >= 1 && choice <= 4)) {
            std::cout << "Please enter a valid choice : ";
            CLEAR_INPUT_BUFFER();
        }
        CLEAR_INPUT_BUFFER();
        switch(choice) {
            case 1 : {
                std::cout << "\nEnter the indices : ";
                while(!(std::cin >> i) || !(std::cin >> j)) {
                    std::cout << "Please enter a valid integer : ";
                    CLEAR_INPUT_BUFFER();
                }
                CLEAR_INPUT_BUFFER();
                std::cout << "Enter the element : ";
                while(!(std::cin >> element)) {
                    std::cout << "Please enter a valid element : ";
                    CLEAR_INPUT_BUFFER();
                }
                CLEAR_INPUT_BUFFER();
                if(mat.store(i, j, element) == __INT_MAX__) {
                    std::cout << "\n*** Illegal index reference ***\n";
                } else {
                    std::cout << std::endl << element << " successfully stored at index (" << i << ", " << j << ")\n";
                }
            } break;

            case 2 : {
                std::cout << "\nEnter the indices : ";
                while(!(std::cin >> i) || !(std::cin >> j)) {
                    std::cout << "Please enter a valid integer : ";
                    CLEAR_INPUT_BUFFER();
                }
                CLEAR_INPUT_BUFFER();
                int element = mat.retrieve(i, j);
                if(element != __INT_MAX__)
                    std::cout << "\nElement retrieved from index (" << i << ", " << j << ") = " << element << std::endl;
            } break;

            case 3 : {
                std::cout << "\nMatrix:\n\n";
                mat.print();
            } break;
        }
        if(choice != 4) {
            std::cout << std::setw(80) << std::setfill('*') << std::endl;
            std::cout << "\n\n\n";
        }
    } while(choice != 4);
    return 0;
}