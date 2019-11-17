#include <iostream>
#include <iomanip>
#include <limits>
#include <queue>

#define CLEAR_INPUT_BUFFER() \
    std::cin.clear(); \
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

// mirrorify function takes two trees, 
// original tree and a mirror tree 
// It recurses on both the trees, 
// but when original tree recurses on left, 
// mirror tree recurses on right and 
// vice-versa 
// void mirrorify(node* root, node** mirror) 
// { 
//     if (root == NULL) { 
//         mirror = NULL; 
//         return; 
//     } 
  
//     // Create new mirror node from original tree node 
//     *mirror = createNode(root->val); 
//     mirrorify(root->left, &((*mirror)->right)); 
//     mirrorify(root->right, &((*mirror)->left)); 
// } 

template <class T>
class BSTNode {
    public:
    T data;
    BSTNode<T>* lchild;
    BSTNode<T>* rchild;
    BSTNode() : data(), lchild(NULL), rchild(NULL) {}
    BSTNode(const T& data) : data(data), lchild(NULL), rchild(NULL) {}
};

template <class T>
class BST {
    private:
    BSTNode<T>* root;
    BST(const BST<T>& other) {}
    BST<T>& operator=(const BST<T>& other) {}
    public:
    BST() : root(NULL) {}
    ~BST() {
        destroyRecursive(root);
    }

    void destroyRecursive(BSTNode<T>* temp) 
    {
        if(temp != NULL) {
            destroyRecursive(temp -> lchild);
            destroyRecursive(temp -> rchild);
            delete temp;
        }
        root = NULL;
        return;
    }

    // iterative approach to searching a key in the tree
    BSTNode<T>* search(const T& key) {
        BSTNode<T>* temp = root;
        while(temp != NULL) {
            if(key == temp -> data) {
                return temp;
            } else if(key < temp -> data) {
                temp = temp -> lchild;
            } else {
                temp = temp -> rchild;
            }
        }
        return NULL;
    }

    // recursive approach to searching a key in the tree
    // BSTNode<T>* search(BSTNode<T>* temp, const T& key) {
    //     if(temp == NULL) {
    //         return NULL;
    //     } 
    //     if(key == temp -> data) {
    //         return temp;
    //     } else if(key < temp -> data) {
    //         return search(temp -> lchild, key);
    //     } else {
    //         return search(temp -> rchild, key);
    //     }
    // }

    // iterative approach to inserting nodes in a tree
    BSTNode<T>* insert(const T& key) {
        BSTNode<T>* temp = root;
        BSTNode<T>* r = NULL;
        BSTNode<T>* newnode = new(std::nothrow) BSTNode<T>(key);
        if(newnode == NULL) {
            return NULL;
        }
        if(root == NULL) {
            root = newnode;
            return root;
        }
        while(temp != NULL) {
            r = temp;
            if(key == temp -> data) {   // checking for duplicate
                return NULL;
            } 
            if(key < temp -> data) {
                temp = temp -> lchild;
            } else {
                temp = temp -> rchild;
            }
        }
        if(key < r -> data) {
            r -> lchild = newnode;
            return newnode;
        } else {
            r -> rchild = newnode;
            return newnode;
        }
        return NULL;
    }

    // recursive approach to inserting nodes in a tree
    // BSTNode<T>* insert(BSTNode<T>* temp, const T& key) {
    //     BSTNode<T>* newnode = NULL;
    //     if(temp == NULL) {
    //         newnode = new(std::nothrow) BSTNode<T>(key);
    //         if(newnode == NULL) {
    //             return NULL;
    //         }
    //         return newnode;
    //     }
    //     if(key < temp -> data) {
    //         temp -> lchild = insert(temp -> lchild, key);
    //     } else if(key > temp -> data){
    //         temp -> rchild = insert(temp -> rchild, key);
    //     }
    //     return temp;
    // }

    long height(BSTNode<T>* temp) {
        long x,y;
        if(temp == NULL) {
            return 0;
        }
        x = height(temp -> rchild);
        y = height(temp -> lchild);
        return (x > y ? (x + 1) : (y + 1));
    }

    long countLeftChildren(BSTNode<T>* temp) {
        long count=0;
        if(temp == NULL) {
            return 0;
        }
        if(temp -> lchild != NULL) {
            count += 1 + countLeftChildren(temp -> lchild);
        }
        if(temp -> rchild != NULL) {
            count += countLeftChildren(temp -> rchild);
        }
        return count;
    }

    BSTNode<T>* findInOrderSuccessor(BSTNode<T>* temp) {
        if(temp == NULL) {
            return temp;
        }
        while(temp -> lchild != NULL) {
            temp = temp -> lchild;
        }
        return temp;
    }

    BSTNode<T>* findInOrderPredecessor(BSTNode<T>* temp) {
        if(temp == NULL) {
            return temp;
        }
        while(temp -> rchild != NULL) {
            temp = temp -> rchild;
        }
        return temp;
    }

    BSTNode<T>* recursiveDelete(BSTNode<T>* temp, const T& key) {
        BSTNode<T>* ptr;        
        if(temp == NULL) {
            return temp;
        }
        if(key < temp -> data) {
            temp -> lchild = recursiveDelete(temp -> lchild, key);
            // std::cout << "\ntemp -> lchild -> data = " << temp -> lchild -> data;
            return temp;
        } else if(key > temp -> data) {
            temp -> rchild = recursiveDelete(temp -> rchild, key);
            return temp;
        } else {
            // temp is pointing to the node that is to be deleted
            // when the node has no child
            if(temp -> lchild == NULL && temp -> rchild == NULL) {
                delete temp;
                temp = NULL;
                return temp;
            } else if(temp -> lchild == NULL) {
                ptr = findInOrderSuccessor(temp -> rchild);     // find the smallest element in the right subtree
                temp -> data = ptr -> data;
                temp -> rchild = recursiveDelete(temp -> rchild, ptr -> data);
            } else if(temp -> rchild == NULL) {
                ptr = findInOrderPredecessor(temp -> lchild);   // find the largest element in the left subtree
                temp -> data = ptr -> data;
                temp -> lchild = recursiveDelete(temp -> lchild, ptr -> data);
            } else {
                // if the node to be deleted has 2 children
                if(height(temp -> lchild) > height(temp -> rchild)) {
                    ptr = findInOrderPredecessor(temp -> lchild);
                    temp -> data = ptr -> data;
                    temp -> lchild = recursiveDelete(temp -> lchild, ptr -> data);
                } else {
                    ptr = findInOrderSuccessor(temp -> rchild);
                    temp -> data = ptr -> data;
                    temp -> rchild = recursiveDelete(temp -> rchild, ptr -> data);
                }
            }
        }
        return temp;
    }

    void printLevelOrder() {
        if(root == NULL) {
            std::cout << "\nBinary search tree is empty!\n";
            return;
        }
        std::queue< BSTNode<T>* > q;
        q.push(root);
        while(!q.empty()) {
            BSTNode<T>* temp = q.front();
            std::cout << temp -> data << "  ";
            q.pop();
            if(temp -> lchild != NULL) {
                q.push(temp -> lchild);
            }
            if(temp -> rchild != NULL) {
                q.push(temp -> rchild);
            }
        }
    }

    BSTNode<T>* returnRoot() {
        return root;
    }

    void inOrder(BSTNode<T>* temp) {
        if(temp == NULL) {
            return;
        }
        inOrder(temp -> lchild);
        std::cout << temp -> data << "  ";
        inOrder(temp -> rchild);
    }

    void preOrder(BSTNode<T>* temp) {
        if(temp == NULL) {
            return;
        }
        std::cout << temp -> data << "  ";
        preOrder(temp -> lchild);
        preOrder(temp -> rchild);
    }

    void postOrder(BSTNode<T>* temp) {
        if(temp == NULL) {
            return;
        }
        postOrder(temp -> lchild);
        postOrder(temp -> rchild);
        std::cout << temp -> data << "  ";
    }
};

int main() {
    int choice;
    BST<int> bst;

    do {
        std::cout << "\t\tBINARY SEARCH TREE DEMO\n\n\t\t"
                << "----------MENU----------\n\t\t"
                << "1. Insert nodes\n\t\t"
                << "2. Search a key\n\t\t"
                << "3. Traverse in-orderly\n\t\t"
                << "4. Traverse pre-orderly\n\t\t"
                << "5. Traverse post-orderly\n\t\t"
                << "6. Traverse level orderly\n\t\t"
                << "7. Delete a node\n\t\t"
                << "8. Count number of left children\n\t\t"
                << "9. Print the height\n\t\t"
                << "10. Exit the program\n\n"
                << "Enter your choice : ";
        while(!(std::cin >> choice) || !(choice >= 1 && choice <= 10)) {
            std::cout << "Please enter a valid choice : ";
            CLEAR_INPUT_BUFFER();
        }
        CLEAR_INPUT_BUFFER();

        switch(choice) {
            case 1 : {
                int val; 
                std::cout << "\nEnter the nodes to be inserted (-1 to finish):\n\n";
                std::cin >> val;
                while(val != -1) {
                    if(std::cin.fail()) {
                        std::cout << "\nPlease enter a valid number : ";
                        CLEAR_INPUT_BUFFER();
                        std::cin >> val;
                    } else {
                        if(bst.insert(val) == NULL) { 
                            std::cerr << "\nERROR\n";
                            exit(-1);
                        } else {
                            std::cin >> val;
                        }
                    }
                }
                CLEAR_INPUT_BUFFER();
                std::cout << "\nBinary Search Tree created successfully!\n";
            }
            break;

            case 2 : {
                int key;
                std::cout << "\nEnter the key to be searched in the tree : ";
                while(!(std::cin >> key)) {
                    std::cout << "Please enter a valid key : ";
                    CLEAR_INPUT_BUFFER();
                }
                CLEAR_INPUT_BUFFER();
                if(bst.search(key)) {
                    std::cout << "\n" << key << " found in the tree!\n";
                } else {
                    std::cout << "\n" << key << " not found in the tree\n";
                }
            }
            break;

            case 3 : {
                std::cout << "\nTree traversed in-orderly:\n";
                bst.inOrder(bst.returnRoot());
            }
            break;

            case 4 : {
                std::cout << "\nTree traversed pre-orderly:\n";
                bst.preOrder(bst.returnRoot());
            }
            break;

            case 5 : {
                std::cout << "\nTree traversed post-orderly:\n";
                bst.postOrder(bst.returnRoot());
            }
            break;

            case 6 : {
                std::cout << "\nTree traversed level-orderly:\n";
                bst.printLevelOrder();
            }
            break;

            case 7 : {
                int val;
                std::cout << "\nEnter the value to be deleted : ";
                while(!(std::cin >> val)) {
                    std::cout << "Please enter a valid value : ";
                    CLEAR_INPUT_BUFFER();
                }
                CLEAR_INPUT_BUFFER();
                if(bst.recursiveDelete(bst.returnRoot(), val) != NULL) {
                    std::cout << "\nNode deleted successfully!\n";
                } else {
                    std::cout << "\nNode not found!\n";
                }
            }
            break;

            case 8 : {
                std::cout << "\nNumber of left children in the tree: ";
                std::cout<<bst.countLeftChildren(bst.returnRoot());
            }
            break;

            case 9 : {
                std::cout << "\nHeight of the tree is " << bst.height(bst.returnRoot());
            }
        }
        if(choice != 10) {
            std::cout << "\n\n\nPress any key to continue...";
            std::getchar();
            std::cout << "\n" << std::endl;
            std::cout << std::setw(80) << std::setfill('*') << std::endl;
            std::cout << "\n\n";
        }
    } while(choice != 10);
    return 0;
}