/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 10
  Problem :- Implementing skiplist
*/
/*IMPORTANT- have a check from a friend*/
#include<iostream>
#include<stdlib.h>
#include<time.h>

#define INT_MAX  32000
#define INT_MIN  -32000
using namespace std;

struct node{                                                    //Defining structure of node
  int value;
  struct node*up;
  struct node*down;
  struct node*left;
  struct node*right;
};



class skiplist{                                                 //Defining class of skiplist
  private:
    struct node* head;
    //int level;

  public:
    skiplist(){                                                 //Defining constructor of the class
      struct node*x = createNode(),*y = createNode();
      x->value = INT_MIN;y->value = INT_MAX;
      x->right = y;
      y->left = x;
      head = x;
      //level = u;

    }

    struct node* createNode(){                                  //function to create a Node
      struct node* t = (struct node*) new node();
      t->value = 0;
      t->up = NULL;
      t->down = NULL;
      t->right = NULL;
      t->left = NULL;
      return t;
    }

    int coinflip(){                                             //function randomly giving 1 or 2

      int r = rand()%2 + 1;
      return r;
    }

    void insertN(struct node* u,struct node*r){                 //function which inserts a node at a specified level
      r->right = u->right;
      r->left = u;
      (r->right)->left = r;
      u->right = r;
      return;
    }

    void createNewLevel(){                                      // function which creates a new level with maximum
      struct node*x = createNode(),*y = createNode();           //and minimum nodes in between
      x->value = INT_MIN;y->value = INT_MAX;
      x->right = y;
      y->left = x;
      struct node*j,*h;
      for(h = head; h!=NULL; h = h->right){
        if(h->value == INT_MAX)break;
      }
      j = h;
      x->down = head;
      head->up = x;
      y->down = j;
      j->up = y;
      head = x;
    }



    void insert(int x){                                         //function to insert a node amoung arbitrary number of levels
      if(search1(x) != NULL)cout<<"Element to be inserted is already present"<<endl;
      else{ struct node* r = createNode();
      r->value = x;
      struct node*e = head;
    /*  while(e->down != NULL){
          if(e->value <= x){
            e = e->right;
          }
          else{
            e = e->left;
            e = e->down;
          }
      }
      while(e->value != INT_MAX){
        if(e->value < x){
          e = e->right;
        }
        else{
          break;
        }
      }*/
      while(1){                                       //finding the appropriate place at the bottomost level to be inserted
        if(e->value < x)e = e->right;
        else{
          if(e->down == NULL)break;
          else{e = e->left->down;}
        }
      }
      e = e->left;

      insertN(e,r)                                    //inserting it at the lowest level
      cout << ":P" << endl;
      /*r->right = e->right;
      r->left = e->right->left;
      e->right->left = r;
      e->right = r;
      */
      int i = coinflip(),headcount =0;
      if(i == 2){                                     //if heads
        headcount++;
        struct node*p  =e->right;
        while(i != 1 && headcount < 6){               // finds the node which has not NULL up pointer or the level beginning node(whichever is earlier)
          struct node* t = createNode();
          t->value = x;
          struct node*y = p;
          while(p->up == NULL && p->value != INT_MIN){
            cout << "Yup "<< endl;
            p = p->left;
          }
          if(p->value == INT_MIN){                    //if the node is level beginning
            if(p->up == NULL){                        //if it is head
              cout << "Yuppie"<< endl;
              createNewLevel();
              insertN(head,t);
              t->down = y;
              y->up = t;
              i = coinflip();
              if(i == 2)headcount++;
              p = t;}
            else{
              p = p->up;
              insertN(p,t);
              t->down = y;
              y->up = t;
              i = coinflip();
              p = t;
            }
          }
          else{                                       //if it is some other node
            cout << "Yuppie1"<< endl;
            p = p->up;insertN(p,t);
            t->down = y;y->up = t;
            i = coinflip();
            if(i == 2)headcount++;
            p = t;}
        }
      }
    }
  }

    void search(int x){                                         //function to check whether a node of that value is present or not
      struct node* u = head->right;
      while(1){
        if(u->value < x){
          u = u->right;
        }
        else if(u->value == x){
          cout << "Present" << endl;
          return;
        }

        else if(u->value == INT_MAX || u->value > x){
          if(u->left->down == NULL){
            cout << "Absent" << endl;
            return;
          }
          else{
            u = u->left;
            u = u->down;
          }
        }
    }
    }

    struct node* search1(int x){                                //function to search a node , returning the node address
      struct node* u = head->right;
      while(1){
        if(u->value < x){
          u = u->right;
        }
        else if(u->value == x){
          return u;break;
        }

        else if( u->value > x){
          if(u->left->down == NULL){
            //cout << "Absent" << endl;
            return NULL;
          }
          else{
            u = u->left;
            u = u->down;
          }
        }
    }
    //while(u->down != NULL){u = u->down;}
    //return u;
    }

    void print(){
      struct node* u = head;
      int i = 0;
      while(u != NULL){
        cout << "Level "<<i <<" contains :- ";
        struct node*y = u->right;
        while(y->value != INT_MAX){
          cout << y->value << " ";
          y = y->right;
        }
        cout << endl;i++;u = u->down;
      }
    }
    void deleteN(struct node* a){                               //function to delete a node from a level
      a->left->right = a->right;
      a->right->left = a->left;
      if(a->down != NULL)a->down->up = NULL;
      free(a);
    }

    void restore(){                                             //function to remove the top empty levels from the skiplist
      struct node* a = head;
      while(a->right->value == INT_MAX && a->down != NULL){
        struct node * s = a->down;
        free(a->right);
        free(a);
        a = s;
        a->up = NULL;
        struct node* g;
        for(g = a->right; g != NULL;g = g->right){
          if(g->value == INT_MAX)break;
        }
        g->up = NULL;
      }
      head = a;
    }

    struct node* getHead(){return head;}                        //get function to access the head

    void del(int x){                                            //deletion of a value from a skiplist
      struct node*t = search1(x);                     //first we search the node
      if(t != NULL){                                  //if present
      while(1){                                       // remove all the nodes with the same value
        if(t->down == NULL){
          deleteN(t);return;
        }
        else{
          struct node* u = t->down;
          deleteN(t);
          t = u;
        }
      }
      //if(head->down != NULL)restore();
    }
    else{
      cout << "Element to be deleted is not present" << endl;
    }
    }
};

int main(){
  srand((unsigned)time(0));

  int n,x;
  skiplist slits;
  while(1){
    cout << "1.insert\n2.print\n3.search\n4.delete"<<endl;
    cin >> n;
    switch (n) {
      case 1:
        cin >> x;
        slits.insert(x);
        break;

      case 2:
        slits.print();
        break;

      case 3:
        cin >> x;
        slits.search(x);
        break;

      case 4:
          cin >> x;
          slits.del(x);
          if(slits.getHead()->down != NULL)
          slits.restore();
          break;

      default:
        return 0;
    }
  }

}
