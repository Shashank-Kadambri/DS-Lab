#include <iostream>
#include <limits>
#include <iomanip>

#define CLEAR_INPUT_BUFFER() \
    std::cin.clear(); \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

class Term {
    public:
        float coeff;
        int power;
        Term* next;
        Term() : coeff(0.0), power(0), next(NULL) {}
        Term(float c, int p) : coeff(c), power(p), next(NULL) {}
};

class Polynomial {
    private:
        Term* head;
        Term* tail;
    public:
        Polynomial() : head(NULL), tail(NULL) {}
        ~Polynomial() {
            destroyPolynomial();
        }

        int addTermToPolynomial(float c, int p) {
            Term* temp = new(std::nothrow) Term(c, p);
            if((temp == NULL) || (c == 0.0 && p == 0)) {
                return -1;
            }
            if(head == NULL) {
                head = tail = temp;
            } else {
                if(p > head -> power) {
                    temp -> next = head;
                    head = temp;
                } else {
                    Term* ptr = head;
                    while((ptr -> next != NULL) && (p < ptr -> next -> power)) {
                        ptr = ptr -> next;
                    }
                    if(ptr -> next == NULL) {
                        tail -> next = temp;
                        tail = temp;
                    } else {
                        temp -> next = ptr -> next;
                        ptr -> next = temp;
                    }
                }
            }
            return 0;
        }

        void print() {
            Term* ptr = head;
            while(ptr != NULL) {
                std::cout << ptr -> coeff << "x^" << ptr -> power;
                if(ptr -> next == NULL) {
                    return;
                } else {
                    std::cout << " + ";
                    ptr = ptr -> next;
                }
            }
            return;
        }

        void destroyPolynomial() {
            Term* temp = head;
            while(temp != NULL) {
                Term* nextterm = temp -> next;
                delete[] temp;
                temp = nextterm;
            }
            head = tail = NULL;
            return;
        }

        void addPolynomials(const Polynomial& poly1, const Polynomial& poly2) {
            Term* ptr1 = poly1.head;
            Term* ptr2 = poly2.head;
            while(ptr1 != NULL && ptr2 != NULL) {
                if(ptr1 -> power == ptr2 -> power) {
                    addTermToPolynomial(ptr1 -> coeff + ptr2 -> coeff, ptr1 -> power);
                    ptr1 = ptr1 -> next;
                    ptr2 = ptr2 -> next;
                } else if(ptr1 -> power > ptr2 -> power) {
                    addTermToPolynomial(ptr1 -> coeff, ptr1 -> power);
                    ptr1 = ptr1 -> next;
                } else {
                    addTermToPolynomial(ptr2 -> coeff, ptr2 -> power);
                    ptr2 = ptr2 -> next;
                }
            }
            if(ptr1 == NULL) {
                while(ptr2 != NULL) {
                    addTermToPolynomial(ptr2 -> coeff, ptr2 -> power);
                    ptr2 = ptr2 -> next;
                }
            } else {
                while(ptr1 != NULL) {
                    addTermToPolynomial(ptr1 -> coeff, ptr1 -> power);
                    ptr1 = ptr1 -> next;
                }
            }
            return;
        }
};

int main() {
    Polynomial poly1, poly2, poly3;
    int p = 1;
    float c = 1.0;
    int i;

    std::cout << "\n\t\tPROGRAM TO ADD TWO POLYNOMIALS\n\n";
    std::cout << "Polynomial 1:\nEnter pairs (coefficient, power) [(0, 0) to terminate]:\n";
    while(true) {
        std::cin >> c >> p;
        if(c == 0.0 && p == 0) {
            break;
        } else if(poly1.addTermToPolynomial(c, p) == -1) {
            std::cout << "\n*** Term could not be added to polynomial ***\n";
            CLEAR_INPUT_BUFFER();
        }
    }
    std::cout << "\nPolynomial 2:\nEnter pairs (coefficient, power) [(0, 0) to terminate]:\n";
    while(true) {
        std::cin >> c >> p;
        if(c == 0.0 && p == 0) {
            break;
        } else if(poly2.addTermToPolynomial(c, p) == -1) {
            std::cout << "\n*** Term could not be added to polynomial ***\n";
            CLEAR_INPUT_BUFFER();
        }
    }
    std::cout << "\nPolynomial 1:\n";
    poly1.print();
    std::cout << "\n\nPolynomial 2:\n";
    poly2.print();
    poly3.addPolynomials(poly1, poly2);
    std::cout << "\n\nResulting polynomial:\n";
    poly3.print();
    return 0;
}