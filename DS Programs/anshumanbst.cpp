#include<iostream>
#include"queue.cpp"
#include"stackll.cpp"
using namespace std;

template<typename T>
class BSTNode {
public:
     BSTNode<T> * left;
     BSTNode<T> * right;
     T info ;

     BSTNode() {
          left = NULL;
          right = NULL;
     }
     BSTNode(T data) {
          left = NULL;
          right = NULL;
          info = data;
     }

};

template<typename T>
class BSTree{
public:
     BSTNode<T> * root;
     BSTree(){
          root = NULL;
     }

     void add(T el){
          BSTNode<T> * p = new BSTNode<T>(el);
          if(root == NULL)
               root = p;
          else{
               BSTNode<T> * q = root;
               while(1) {
                    if(q->info>el){
                         if(q->left == NULL){
                              q->left = p;
                              return;
                         }
                         q = q->left;
                    }
                    else{
                         if(q->right == NULL){
                              q->right = p;
                              return;
                         }
                         q = q->right;
                    }
               }
          }
     }

     void traverse(){
          if(root == NULL)
               return ;
          Queue<BSTNode<T>*> * q = new Queue<BSTNode<T>*>();
          q->enqueue(root);
          while(!q->isEmpty()){
               BSTNode<T> * t = q->dequeue()->info;
               cout<<t->info<<" ";
               if(t->left!=NULL)
                    q->enqueue(t->left);
               if(t->right!=NULL)
                    q->enqueue(t->right);
          }

     }

     int countLeftNonRec(){
          if(root == NULL)
               return 0 ;
          int c=0;
          Queue<BSTNode<T>*> * q = new Queue<BSTNode<T>*>();
          q->enqueue(root);
          while(!q->isEmpty()){
               BSTNode<T> * t = q->dequeue()->info;
               cout<<t->info<<" ";
               if(t->left!=NULL){
                    q->enqueue(t->left);
                    c++;
               }
               if(t->right!=NULL)
                    q->enqueue(t->right);
          }
          return c;
     }

     void getHeightNonRec(){
          if(root == NULL)
               return ;
          Queue<BSTNode<T>*> * q = new Queue<BSTNode<T>*>();
          q->enqueue(root);
          while(!q->isEmpty()){
               BSTNode<T> * t = q->dequeue()->info;
               cout<<t->info<<" ";
               if(t->left!=NULL)
                    q->enqueue(t->left);
               if(t->right!=NULL)
                    q->enqueue(t->right);
          }

     }


     void visit(BSTNode<T> * node){
          cout<<node->info<<" ";
     }
     void inOrder(){
          if(root ==NULL)
               return;
          SLLStack<BSTNode<T>*> stck;
          BSTNode<T> * p = root;
          stck.push(root);
          while(p->left!=NULL){
               stck.push(p->left);
               p = p->left;
          }
          while(!stck.isEmpty()){
               BSTNode<T> * q = stck.topel()->info;
               stck.pop();
               visit(q);
               if(q->right!=NULL){
                    stck.push(q->right);
                    BSTNode<T> * r = q->right;
                    while(r->left!=NULL){
                         stck.push(r->left);
                         r = r->left;
                    }
               }
          }

     }

     int preOrder(){//visit before push
          if(root == NULL)
               return 0;
          int c=0;//temp
          SLLStack<BSTNode<T>*> stck;
          BSTNode<T> * p = root;
          visit(p);
          stck.push(p);
          while(p->left != NULL){
               c++;
               visit(p->left);
               stck.push(p->left);
               p = p->left;
          }
          while(!stck.isEmpty()){
               BSTNode<T> * q = stck.topel()->info;
               stck.pop();
               if(q->right!= NULL){
                    visit(q->right);
                    stck.push(q->right);
                    BSTNode<T> * r = q->right;
                    while(r->left!=NULL){
                         visit(r->left);
                         c++;
                         stck.push(r->left);
                         r = r->left;
                    }

               }
          }
          return c;
     }

     void postOrder(){
          if(root ==NULL)
               return;
          SLLStack<BSTNode<T>*> stck;
          BSTNode<T> * p = root;
          stck.push(root);
          while(p->left!=NULL){
               stck.push(p->left);
               p = p->left;
          }
          while(!stck.isEmpty()){
               BSTNode<T> * q = stck.topel()->info;
               if(q->right!=NULL){
                    stck.push(q->right);
                    BSTNode<T> * r = q->right;
                    while(r->left!=NULL){
                         stck.push(r->left);
                         r = r->left;
                    }
               }
               else{
                    visit(q);
                    stck.pop();
               }
               while(stck.topel()!=NULL){
                    BSTNode<T> * t = stck.topel()->info;
                    if(t->right== q){
                         visit(t);
                         stck.pop();
                         q = t;
                    }
                    else{
                         break;
                    }
               }
          }
     }
     void preOrderRec(BSTNode<T> * p){
          if(p == NULL){
               return;
          }
          cout<<p->info<<" ";
          if(p->left!=NULL)
          preOrderRec(p->left);
          if(p->right!=NULL)
               preOrderRec(p->right);
     }
     void postOrderRec(BSTNode<T> * p){
          if(p == NULL)
               return;
          if(p->left!=NULL){
               postOrderRec(p->left);
          }
          if(p->right!=NULL){
               postOrderRec(p->right);
          }
          cout<<p->info<<" ";

     }
     void inOrderRec(BSTNode<T> * p){
          if(p == NULL){
               return;
          }
          if(p->left!=NULL)
               inOrderRec(p->left);
          cout<<p->info<<" ";
          if(p->right!=NULL){
               inOrderRec(p->right);
          }
     }
    
     bool search(T el){
          BSTNode<T> * p = root;
          while(p!=NULL){
               if(el>p->info){
                    p = p->right;
               }
               else if(el<p->info){
                    p = p->left;
               }
               else{
                    return true;
               }
          }
          return false;
     }

     bool deleteEl(T el){

          BSTNode<T> * p = root;
          BSTNode<T> * parent=NULL;
          while(p!=NULL){
               if(el>p->info){
                    parent = p;
                    p = p->right;
               }
               else if(el<p->info){
                    parent = p;
                    p = p->left;
               }
               else{
                    break;
               }
          }
          if(p == NULL){
               return false;
          }
          BSTNode<T> * lchild = p->left;
          BSTNode<T> * rchild = p->right;
          if(lchild == NULL && rchild == NULL){
               if(parent != NULL){
                    if(p->info < parent->info){
                         parent->left == NULL;
                    }
                    else{
                         parent->right == NULL;
                    }
               }
               delete p;
          }
          else if((lchild == NULL && rchild!=NULL) || (lchild!=NULL && rchild == NULL)){
               if(parent!=NULL){
                    if(lchild != NULL){

                         if(p->info < parent->info )
                              parent->left = lchild;
                         else
                              parent->right = lchild;
                    }
                    else{
                         if(p->info < parent->info )
                              parent->left = rchild;
                         else
                              parent->right = rchild;
                    }
               }
               else{
                    if(lchild!=NULL)
                         root = lchild;
                    else
                         root = rchild;
               }
               delete p;
          }
          else{
               //deletion by copying
               BSTNode<T> * temp = lchild;
               if(temp->right!=NULL){
                    while(temp->right->right!=NULL){
                         temp = temp->right;
                    }

                    p->info = temp->right->info;
                    BSTNode<T>*t = temp->right->left;
                    delete temp->right;
                    temp->right = t;
               }
               else{
                    p->info = temp->info;
                    p->left = temp->left;
                    delete temp;
               }

          }
          return true;
     }

     int countRec(BSTNode<T> * p,int c = 0,int max = 0){
         
          if(p->left == NULL && p->right == NULL){
               if(max<c){
                    max=c;
               }
               return max;
          }
          if(p->left!=NULL){
               max = countRec(p->left,c+1,max);
          }
          if(p->right!=NULL){
               max = countRec(p->right,c+1,max);
          }
          return max;
     }

     int countNonLeaf(BSTNode<T> * p){
          int c=0;
          if(p->left || p->right){
               c++;
               if(p->left!=NULL){
                    c+=countNonLeaf(p->left);
               }
               if(p->right!=NULL){
                    c+=countNonLeaf(p->right);
               }
          }
          return c;
     }
          
         
    
};


int main(){
     BSTree<int> * tree = new BSTree<int>();
     int ch,exit=0;
     while(exit==0){
          cout<<"* * * M E N U * * *";
         
          switch(ch){
               case 1:

              
     }
     }
    
     tree->add(40);
     tree->add(30);
     tree->add(28);
     tree->add(50);
     tree->add(45);
     tree->add(44);
     tree->add(41);
     tree->add(43);
     tree->add(42);
     tree->add(36);
     tree->add(52);
     tree->add(54);
     tree->add(53);
     tree->add(57);
     tree->add(34);

     //tree->add(10);
     //tree->add(5);
     //tree->add(11);
     //tree->add(4);
     //tree->add(6);
     //tree->add(13);
     //tree->add(12);

     cout<<"\nLevelwise Traverse:";
     tree->traverse();
     cout<<"\nDepth-wise in order Traverse:";
     tree->inOrder();
     cout<<"\nDepth-wise pre order Traverse:";
     int mleftCount = tree->preOrder();
     cout<<"No.of left child:"<<mleftCount;
     cout<<"\nDepth-wise post order Traverse:";
     tree->postOrder();
     cout<<"\nRecursive :-";
     cout<<"\nDepth-wise in order Traverse:";
     tree->inOrderRec(tree->root);
     cout<<"\nDepth-wise pre order Traverse:";
     tree->preOrderRec(tree->root);
     cout<<"\nDepth-wise post order Traverse:";
     tree->postOrderRec(tree->root);
     cout<<"\nNo of Non leaf roots:"<<tree->countNonLeaf(tree->root);


     /*cout<<endl<<tree->deleteEl(1);
     cout<<"\nLevelwise Traverse:";
     tree->traverse();
     cout<<"\nIs 1 present:";
     if(tree->search(1)){
          cout<<"Yes";
     }
     else{
          cout<<"No";
     }*/
    


}