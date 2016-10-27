#include<iostream>
using namespace std;

struct node{
  int val;
  struct node* left;
  struct node* right;
  struct node* parent;
};

class BinarySearchTree{
  private:
    struct node* root;

  public:
    BinarySearchTree(){
      root = NULL;
    }
    struct node* createNode(){
      struct node * x = (struct node*)new node;
      return x;

    }

    void insert(struct node* x){
      struct node*y = NULL;
      struct node*p = root;
      while(p != NULL){
        y = p;
        if(x->val < p->val){
          p = p->left;
        }
        else p = p->right;
      }
      x->parent = y;
      if(y == NULL){
        root = x;
      }
      else if(x->val < y->val){
        y->left = x;
      }
      else{
        y->right = x;
      }
    }
    void inorder(struct node* x){
      if(x != NULL){
        inorder(x->left);
        cout << x->val << " ";
        inorder(x->right);
      }
    }
    struct node* getRoot(){
      return root;
    }
    struct node* search(int value){
      struct node* x = root,*y = NULL;
      while(x != NULL){
        if(x->val == value){
          y = x;
          return y;

        }
        else if(x->val < value ){
          x = x->right;
        }
        else{
          x = x->left;
        }
      }
      if(x == NULL){
        return NULL;
      }
    }
    struct node* minimum(struct node* x){
      struct node* y = NULL,*z=x;
      while(x != NULL){
        y = x;
        x = x->left;
      }
      return y;

    }

    struct node* maximum(struct node* x){
      struct node* y = NULL,*z = x;
      while(x != NULL){
        y = x;
        x = x->right;
      }
      return y;

    }
    struct node* successor(struct node* s){
      if(s->right != NULL){
        return minimum(s->right);
      }
      return NULL;
    }

    struct node* predecessor(struct node* s){
      if(s->left != NULL){
        return maximum(s->left);
      }
      return NULL;
    }
    void del(int value){
      struct node* x = search(value);
      if(x != NULL){
        if(x->left == NULL && x->right == NULL){
          struct node* y = x->parent;
          if(y->val < x->val){
            y->right = NULL;
          }
          else{
            y->left = NULL;
          }
        }
        else{
          struct node *y = NULL,*z = NULL;
          if(x->left != NULL){
            y = predecessor(x);
          }
          if(x->right != NULL){
            z = successor(x);
          }
          if(y != NULL){
            //Swap predeccessor and x
            int temp = y->val;
            y->val = x->val;
            x->val = temp;
            // Delete the new predecessor node
            struct node* p = y->parent;
            if(p->val < y->val){
              p->right = NULL;
            }
            else p->left = NULL;
          }
          else{
            //Swap successor and x
            int temp = z->val;
            z->val = x->val;
            x->val = temp;
            // Delete the new predecessor node
            struct node* p = z->parent;
            if(p->val < z->val){
              p->right = NULL;
            }
            else p->left = NULL;
          }
        }
      }
    }
};


int main(){
  BinarySearchTree bin;
  int n,x,a;
  while(1){
    cout << "***Menu***\n1.insert\n2.inorder traversal\n3.delete "<< endl;
    cin >> n;
    switch (n) {
      case 1:
      {
      struct node* p = bin.createNode();
      cout << "Enter the value to be inserted" << endl;
      cin >> p->val;
      bin.insert(p);
      break;}

      case 2:
      bin.inorder(bin.getRoot());
      break;

      case 3:
      cout << "Enter the element to be deleted" << endl;
      cin >> a;
      bin.del(a);
      break;

      default:
      return 0;
    }
  }
}
