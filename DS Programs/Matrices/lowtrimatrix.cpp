#include <iostream>
#include <limits>
#include <iomanip>

#define CLEAR_INPUT_BUFFER() \
    std::cin.clear(); \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

template <class T>
class LowerTriangularMatrix {
    private:
        int n;
        T* arr;
    public:
        LowerTriangularMatrix() : n(0), arr(NULL) {}
        LowerTriangularMatrix(const int& n) : n(n) {
            arr = new(std::nothrow) T[n];
        }
        ~LowerTriangularMatrix() {
            delete[] arr;
        }

        int store(const int& i, const int& j, const T& val) {
            if(i < 1 || j < 1 || i > n || j > n) {
                return __INT_MAX__;
            }
            if(i >= j) {
                arr[(i * (i - 1) / 2 + j) - 1] = val;
                return 0;
            } else {
                return __INT_MAX__;
                // don't know
            }
        }

        T retrieve(const int& i, const int& j) const {
            if(i < 1 || j < 1 || i > n || j > n) {
                std::cout << "\n*** Illegal index reference ***\n";
                return __INT_MAX__;
            } 
            if(i >= j) {
                return arr[i * (i - 1) / 2 + j - 1];
            } else {
                return 0;
            }
        }

        void print() {
            for(int i = 1; i <= n; ++i) {
                for(int j = 1; j <= n; ++j) {
                    // if(i < j) {
                    //     std::cout << 0 << "  ";
                    // } else {
                    //     std::cout << arr[i] << "  ";
                    // }
                    std::cout << retrieve(i ,j) << "  ";
                }
                std::cout << std::endl;
            }
            return;
        }
};

int main() {
    int dim, choice, element, i, j;
    std::cout << "\n\t\t*** LOWER TRIANGULAR MATRIX ***\n\nEnter the dimension : ";
    while(!(std::cin >> dim) || (dim < 1)) {
        std::cout << "Please enter a valid dimension : ";
        CLEAR_INPUT_BUFFER();
    }
    CLEAR_INPUT_BUFFER();
    LowerTriangularMatrix<int> mat(dim);
    do {
        std::cout << "\n\t\tLOWER TRIANGULAR MATRIX\n\n\t\t"
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