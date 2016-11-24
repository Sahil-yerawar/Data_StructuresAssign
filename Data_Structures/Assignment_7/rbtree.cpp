/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 5
  Problem :- implementing red-black tree
*/
#include<iostream>
using namespace std;

enum Color {red,black};                                         //defining a map for colour to integer
struct node{                                                    //declaring a structure for node in a rbTree
  int val;
  struct node* left;
  struct node* right;
  struct node* parent;
  Color color;
};

class RBTree{                                                   //declaring a class for red black tree
  private:
    struct node* root;
    struct node* nil;

  public:
    RBTree(){                                                   //constructor for initializing the object
      nil = createNode();
      root = nil;
    }
    struct node* createNode(){                                  //function to create a node
      struct node * x = (struct node*)new node;
      x->left = nil;
      x->right = nil;
      x->parent = nil;
      x->color = black;
      return x;

    }
    void left_rotate(struct node*x){                             //function to left rotate a red black tree
      struct node* y = x->right;
      x->right = y->left;
      if(y->left != nil){
        y->left->parent = x;
      }
      y->parent = x->parent;
      if(x == root){
        root = y;
      }
      else if(x == x->parent->right){
        x->parent->right = y;
      }
      else x->parent->left = y;
      y->left = x;
      x->parent = y;
    }

    void right_rotate(struct node*x){                           //function to right rotate a red black tree
      struct node* y = x->left;
      x->left = y->right;
      if(y->right != nil){
        y->right->parent = x;
      }
      y->parent = x->parent;
      if(x == root){
        root = y;
      }
      else if(x == x->parent->right){
        x->parent->right = y;
      }
      else x->parent->left = y;
      y->right = x;
      x->parent = y;
    }

    void insert_fixup(struct node* z){                          //fixing function to restore the properties of the red black tree
        while(z->parent->color == red){
          if(z->parent == z->parent->parent->left){
            struct node* y = z->parent->parent->right;
            if(y->color == red){
              z->parent->color = black;
              y->color  = black;
              z->parent->parent->color = red;
              z = z->parent->parent;
            }
            else if(z->parent->right == z){
              z = z->parent;
              left_rotate(z);
            }
            else {
              z->parent->color = black;
              z->parent->parent->color = red;
              right_rotate(z->parent->parent);
            }
          }
          else{
            struct node* y = z->parent->parent->left;
            if(y->color == red){
              z->parent->color = black;
              y->color  = black;
              z->parent->parent->color = red;
              z = z->parent->parent;
            }
            else if(z->parent->left == z){
              z = z->parent;
              right_rotate(z);
            }else{
              z->parent->color = black;
              z->parent->parent->color = red;
              left_rotate(z->parent->parent);
            }
          }
        }
        root->color = black;
    }



    void insert(struct node* x){                                //function to insert a node in the red black tree
      struct node*y = nil;
      struct node*p = root;
      while(p != nil){
        y = p;
        if(x->val < p->val){
          p = p->left;
        }
        else p = p->right;
      }
      x->parent = y;
      if(y == nil){
        root = x;
        root->parent = nil;
      }
      else if(x->val < y->val){
        y->left = x;
      }
      else{
        y->right = x;
      }
      x->left = nil;
      x->right = nil;
      x->color = red;
      insert_fixup(x);
    }

    void inorder(struct node* x){                               //inorder traversal of the red black tree
      if(x != nil){
        inorder(x->left);
        if(x->color == 1)
        cout << x->val << "(black)" << " " ;

        else cout << x->val << "(red)" << " " ;
        inorder(x->right);
      }

    }
    struct node* getRoot(){                                     //get function to access the red black tree
      return root;
    }
    struct node* search(int value){                             //function to search the value in the red black tree
      struct node* x = root,*y = nil;
      while(x != nil){
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
      if(x == nil){
        return nil;
      }
    }
    struct node* minimum(struct node* x){                       //function to find the node with minimum value in the red black tree
      struct node* y = nil;
      while(x != nil){
        y = x;
        x = x->left;
      }
      return y;

    }

    struct node* maximum(struct node* x){                       //function to find the node with maximum value in the red black tree
      struct node* y = NULL;
      while(x != NULL){
        y = x;
        x = x->right;
      }
      return y;

    }
    struct node* successor(struct node* s){                     //function to find the node with value just more than the concerned node
      if(s->right != NULL){
        return minimum(s->right);
      }
      return NULL;
    }

    struct node* predecessor(struct node* s){                   //function to find the node with vlaue just less than the concerned node
      if(s->left != NULL){
        return maximum(s->left);
      }
      return NULL;
    }
    int getParent(int Value){                                   //function to get the parent node of the given node
      struct node* x = search(Value);
      if(x == NULL) return -2;
      if(x->parent != NULL) return (x->parent)->val;
      else return -1;
    }
    void transplant(struct node*x, struct node*y){              //function to transplant the given nodes
      if(x->parent == nil){
        root = y;
      }
      else if(x->parent->left == x){
        x->parent->left = y;
      }
      else x->parent->right = y;
      y->parent = x->parent;
    }

    void delete_fixup(struct node*x){                           //fixup function to restore the properties of the red black tree
      struct node* w;
      while(x != root && x->color == black){
        if(x == x->parent->left){
          w = x->parent->right;
          if(w->color == red){
            w->color = black;
            x->parent->color = red;
            left_rotate(x->parent);
            w = x->parent->right;
          }
          if(w->left->color == black && w->right->color == black){
            w->color = red;
            x = x->parent;
          }
          else if(w->right->color == black){
            w->left->color = black;
            w->color = red;
            right_rotate(w);
            w = x->parent->right;
          }else{
            w->color = x->parent->color;
            x->parent->color = black;
            w->right->color = black;
            left_rotate(x->parent);
            x = root;
          }
        }
        else{
          w = x->parent->left;
          if(w->color == red){
            w->color = black;
            w->parent->color = red;
            right_rotate(x->parent);
            w = x->parent->left;
          }
          if(w->right->color == black && w->left->color == black){
            w->color = red;
            x = x->parent;
          }
          else if(w->left->color == black){
            w->right->color = black;
            w->color = red;
            left_rotate(w);
            w = x->parent->left;
          }else{
            w->color = x->parent->color;
            x->parent->color = black;
            w->left->color = black;
            right_rotate(x->parent);
            x = root;
          }
        }
      }
      x->color = black;
    }
    void del(int value){                                        //function to delete a value from the red black tree

      struct node* x = search(value);

      if(x != nil){
        struct node* a = x,*z;
        Color org_color = a->color;
        if(x->left == nil){
          z = x->right;
          transplant(x,x->right);
        }
        else if(x->right == nil){
          z = x->left;
          transplant(x,x->left);
        }
        else{
          a = minimum(x->right);
          org_color = a->color;
          z = a->right;
          if(a->parent == x){
            z->parent = a;
          }
          else{
            transplant(a,a->right);
            a->right = x->right;
            a->right->parent = a;
          }
          transplant(x,a);
          a->left = x->left;
          a->left->parent = a;
          a->color = x->color;

        }
        if(org_color == black){
          delete_fixup(z);
        }
      }

    }
  };

int main(){
  RBTree bin;
  int n,x,a;
  while(1){
    cout << "***Menu***\n1.insert\n2.inorder traversal\n3.delete"<<endl;
    cin >> n;
    switch (n) {
      {case 1:
      struct node* p = bin.createNode();
      cout << "Enter the value to be inserted" << endl;
      cin >> p->val;
      bin.insert(p);
      break;
}
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

      default:
      return 0;
    }
  }
}
