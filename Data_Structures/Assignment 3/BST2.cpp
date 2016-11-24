#include<iostream>
using namespace std;

struct node{
  int val;
  struct node* left;
  struct node* right;
  //struct node* parent;
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
      x->left = NULL;
      x->right = NULL;
      //x->parent = NULL;
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
      //x->parent = y;
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
      struct node* y = NULL;
      while(x != NULL){
        y = x;
        x = x->left;
      }
      return y;

    }

    struct node* maximum(struct node* x){
      struct node* y = NULL;
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
    /*int getParent(int Value){
      struct node* x = search(Value);
      if(x == NULL) return -2;
      if(x->parent != NULL) return (x->parent)->val;
      else return -1;
    }*/

    struct node* getParent(int value){
      /*if(root->val == value) return NULL;
      struct node *x= search(value),*a = root,*b = NULL;
      while(a != NULL){
        if((a->left)->val == value || (a->right)->val == value){
          //cout << a->val << endl;
          return a;
        }
        else{
          if(a->val < value){
              a = a->right;

          }
          else if(a->val > value){
            a = a->left;
          }
        }
      }
    if(a == NULL) return NULL;
*/

struct node* x = root,*y = NULL;
while(x != NULL){
  if(x->val == value){
    //y = x;
    return y;

  }
  else if(x->val < value ){
    y = x;
    x = x->right;
  }
  else{
    y = x;
    x = x->left;
  }
}
if(x == NULL){
  return NULL;
}
}
    void del(int value){

      struct node* x = search(value);

      if(x != NULL){
        if(x->left == NULL && x->right == NULL){
          struct node* y = getParent(value);//x->parent;
          if(y == NULL) {root = NULL;return;}     // symbolizing the leaf node is a root(only node in the tree)
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
            struct node* p = getParent(y->val);
            int temp = y->val;
            y->val = x->val;
            x->val = temp;
            // Delete the new predecessor node
            //y->parent;
            if(p == x){
              x->left = y->left;
              //if(y->left != NULL) (y->left)->parent = x;
            }
            else{
              struct node* a = y->left;
              //if(a != NULL) a->parent = p;
              p->right = a;
            }

          }


        else{
            //Swap successor and x
            struct node* p = getParent(z->val);
            int temp = z->val;
            z->val = x->val;
            x->val = temp;
            // Delete the new predecessor node
            //z->parent;
            if(p == x){
                x->right = z->right;
                //if(z->right != NULL) (z->right)->parent = x;
            }
            else{
              struct node* a = z->right;
              //if(z->right != NULL) a ->parent = p;
              p->right = a;
            }
          }
        }
      }

    }
  };



int main(){
  BinarySearchTree bin;
  int n,x,a;
  while(1){
    cout << "***Menu***\n1.insert\n2.inorder traversal\n3.delete\n4.get parent"<< endl;
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
      if(bin.getRoot() == NULL){
        cout << "Tree is empty" << endl;
        break;
      }
      cout << "Enter the element to be deleted" << endl;
      cin >> a;
      bin.del(a);
      break;

      case 4:
      cout << "Enter the element to get parent of" << endl;
      cin >> a;
      if(bin.getParent(a) == NULL)cout<< "The node is either root or not present in the tree"<<endl;
      else cout << (bin.getParent(a))->val << endl;
      break;

      default:
      return 0;
    }
  }
}
