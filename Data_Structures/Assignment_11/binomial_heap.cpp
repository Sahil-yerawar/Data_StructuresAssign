/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 11
  Problem :- Implementing Binomial Heap and it's operations- insert, search, delete minimum, find minimum*/
#include<iostream>
#include<stdlib.h>
#include<queue>

using namespace std;

/* defining a node to be used in binomial_tree, whose set is called a binomial heap*/
struct node{
  int value;
  struct node* parent;
  struct node* child;
  struct node* sibling;
  int degree;
};

/*class denoting binomial heaop and its functions*/
class binomial_heap{
  private:
    struct node* head;

  public:
    binomial_heap(){                                            //custom constructor for defining binomial_heap
      head = NULL;
    }

    binomial_heap createHeap(){                                 //creation of a new heap and returning the object
      binomial_heap x;
      return x;
    }

    struct node* createNode(){                                  // creation of a new node
      struct node* g = (struct node*)new node();
      g->value = 0;
      g->child = NULL;
      g->sibling = NULL;
      g->parent = NULL;
      g->degree = 0;
      return g;
    }

    struct node* getMinimum(){                                  // finding the minimum of the given heap
      struct node* x = head,*y = NULL;
      int min = 3000;
      while(x != NULL){                              //it is simply finding the minimum among all the tree roots
        if(x->value  < min){                         //itself minimum among the trees
          min = x->value;
          y = x;
        }
        x = x->sibling;
      }
      return y;
    }
    struct node* getHead(){                                     //get function to access the head
      return head;
    }
    void changeHead(struct node* x){                            //set function for changing the head of the heap
      head = x;
    }
    void binomial_link(struct node* a, struct node* b){         //helper function to link two trees
      a->parent = b;
      a->sibling =b->child;                           //basically, it compares the roots of two trees
      if(b->child != NULL)b->child->parent = NULL;    //the larger one becomes the child of the other tree, making it the new child
      b->child = a;                                   //subsequent pointer corrections and new sibling declarations
      b->degree += 1;
    }

    struct node* binomial_heap_merge(struct node* a){           //helper function to merge two binomial heaps
      if(head == NULL && a == NULL)return NULL;
      else if(head != NULL && a == NULL ){            //the general procedure is similar to merge procedure in mergesort algorithm
         return head;
      }
      else if(head == NULL && a != NULL){
        return a;
      }
      else{
      binomial_heap h = createHeap();
      int isHead = 0;
      struct node *b = head,*c = a,*x = NULL;
      while(b != NULL && c!=NULL){
        if(b->degree <= c->degree){
          if(isHead == 0){
            isHead = 1;
            h.changeHead(b);
            x = b;
          }
          else{
            x->sibling = b;
            x = b;
          }
          b = b->sibling;
        }
        else{
          if(isHead == 0){
            isHead = 1;
            h.changeHead(c);
            x = c;
          }
          else{
            x->sibling = c;
            x = c;
          }
          c = c->sibling;
        }
      }
      if(b != NULL){
        while( b != NULL){
          if(isHead == 0){
            h.changeHead(b);
            x = b;
            b = b->sibling;
          }
          else{
          x->sibling = b;
          x = b;
          b = b->sibling;
        }
        }
      }
      if(c != NULL){
        while(c != NULL){
          if(isHead == 0){
            h.changeHead(c);
            x = c;
            c = c->sibling;
          }
          else{
          x->sibling = c;
          x = c;
          c = c->sibling;
        }
        }
      }
      return  h.getHead();
    }
    }

    binomial_heap union1(struct node *a){                       //function to get the union of two heaps with each degree occuring only once
      binomial_heap d = createHeap();
      d.changeHead(binomial_heap_merge(a));           // create a new heap, and merge the two given heaps in it
      if(d.getHead() == NULL)return d;
      struct node *prev_x = NULL, *x = d.getHead(), *next_x = d.getHead()->sibling;
      while(next_x != NULL){
        if(x->degree != next_x->degree ||(next_x->sibling != NULL && x->degree == next_x->sibling->degree)){
          prev_x = x;                                 //traversal condition when link is not possible
          x = next_x;
        }
        else{
          if(x->value <= next_x->value){              //if linking is possible, check the values then link
            x->sibling = next_x->sibling;
            binomial_link(next_x,x);
          }
          else{
            if(prev_x == NULL){                       //if the node to be linked is the head node, change the head
              d.changeHead(next_x);

            }
            else prev_x->sibling = next_x;            //if not head, remove the concerned node and link it
            binomial_link(x,next_x);
            x = next_x;
          }
        }
        next_x = x->sibling;                          //traversal statement
      }
      a = NULL;
      return d;
    }
    void printNode1(struct node* a){
      queue<struct node*> nodeList;
      queue<struct node*> &u = nodeList;
      nodeList.push(a);
      struct node *curr = a->child;
      while(curr != NULL){
        nodeList.push(curr);
        curr = curr->sibling;
      }//cout<<"Hi"<<endl;
      cout << (nodeList.front())->value << " ";
      nodeList.pop();
      printNode10(nodeList);
    }
    void printNode10(queue<struct node*> &a){
      if(a.empty()){
        return;
      }
      else{
        struct node* curr = a.front()->child;
        while(curr != NULL){
          a.push(curr);
          curr = curr->sibling;
        }
        cout << (a.front())->value << " ";
        a.pop();
        printNode10(a);
      }
    }
    void print(){                                               //printing of a binomial heap
      for(struct node* x = head; x != NULL; x = x->sibling){
        if(x->sibling == NULL){                       //sequential access of root nodes and printing the binary trees in it
          int isRoot = 0;
          cout << "( ";
          printNode1(x);
          cout << ")" << endl;
        }
        else{
        int isRoot = 0;
        cout << "( ";
        printNode1(x);
        cout << ")--->";
      }
    }

    }

    void printNode(struct node* a, int r){                      //printing of individual nodes to form trees
      if (a == NULL)return;                           //if the node is NULL, just return
      else if(a->parent == NULL && r == 0){           //if the node is a root node, print the value , and recursively call it on it's child
        cout << a->value <<" ";
        a = a->child;
        r = 1;
        printNode(a,r);

      }

      else{                                           //else print the value, recursively call it on its child as well as it's sibling

        cout << a->value<<" ";
        struct node*b = a->sibling;
        a = a->child;

        printNode(a,r);
        printNode(b,r);
    }
  }


    void insert(int x){                                         //function to insert a value in the heap
        struct node* g = createNode();
        g->value = x;
        binomial_heap h = createHeap();
        h.changeHead(g);
        head = union1(g).getHead();
        return;
    }

    void del_min(){                                             //function to delete the minimum value in the heap
      if(head == NULL)cout<<"There is no minimum element as heap is empty"<<endl; //check for the empty heap case
      else{
      struct node *d = getMinimum();                  //get the minimum value in the heap
      if(d == head)head = head->sibling;              //if head, shift the head to its next value
      else{
      struct node* u;                                 //or find the previous root and remove the cuurent root from the heap
      for( u = head; u != NULL; u = u->sibling){
        if(u->sibling == d)break;
      }
      u->sibling = d->sibling;
      }
      binomial_heap h = createHeap();                 //create a new heap for union purposes
      if(d->child == NULL){                           //check if the root is the only node in the tree
        free(d);
        return;
      }
      else{
      struct node*prev = NULL,*x = d->child,*y=d->child->sibling;
      x->parent = NULL;
      free(d);
      while(x != NULL){                               //reverse the list of children
        x->sibling = prev;
        prev = x;
        x = y;
        if(y!=NULL)y = y->sibling;

      }
      h.changeHead(prev);
       head = this->union1(h.getHead()).getHead();  // union of this list with the original one
    }
      }
    }

};


int main(){
  binomial_heap h1,h2;
  int n,x,m,y;
  /*menu form to ask for functions, each applied on both the heaps(except union)*/
  while(1){
    cout<<"Heaps:- 0->h1, 1->h2\n***Menu***\n1.insert\n2.union\n3.find_minimum\n4.print\n5.delete minimum"<<endl;
    cin >> n;
    switch (n) {
      case 1:
        cout << "Please select the target heap, then the number t be inserted" << endl;
        cin >> y >> x;

        if(y == 0){
          h1.insert(x);
        }
        else if(y == 1){
          h2.insert(x);
        }
        else{
          cout << "Please enter the appropriate choice"<<endl;
        }
        break;

      case 2:
        h1.changeHead(h1.union1(h2.getHead()).getHead());
        h2.changeHead(NULL);
        break;


      case 3:
        cout << "Please select the target heap" << endl;
        cin >> y ;
        if(y == 0){
          cout << h1.getMinimum()->value << endl;

        }
        else if(y == 1)cout << h2.getMinimum()->value << endl;

        else{
          cout << "Please enter the appropriate choice"<<endl;
        }
        break;

      case 4:
      h1.print();
      h2.print();
      break;

      case 5:
      cout << "Please select the target heap" << endl;
      cin >> y ;
      if(y == 0)h1.del_min();
      else if(y == 1) h2.del_min();

      else{
        cout << "Please enter the appropriate choice"<<endl;
      }
      break;

      default:
        return 0;
    }
  }
}
