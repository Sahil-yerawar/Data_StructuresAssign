#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

struct node{
  int value;
  struct node*up;
  struct node*down;
  struct node*left;
  struct node*right;
};



class skiplist{
  private:
    struct node* head;
    int level;

  public:
    skiplist(int u){
      struct node*x = createNode(),*y = createNode();
      x->value = -3000;y->value = 3000;
      x->right = y;
      y->left = x;
      head = x;
      for(int i = 0; i < u-1; i++){
        struct node*x = createNode(),*y = createNode();
        x->value = -3000;y->value = 3000;
        x->right = y;
        y->left = x;
        x->down = head;
        head->up = x;
        y->down = head->right;
        head->right->up = y;
        head = x;
      }
      level = u;

    }

    struct node* createNode(){
      struct node* t = (struct node*) new node();
      t->value = 0;
      t->up = NULL;
      t->down = NULL;
      t->right = NULL;
      t->left = NULL;
      return t;
    }

    int coinflip(){

      int r = rand()%2 + 1;
      return r;
    }

    void insertN(struct node* u,struct node*r){
      r->right = u->right;
      r->left = u;
      (u->right)->left = r;
      u->right = r;
      return;
    }

    void createNewLevel(){
      struct node*x = createNode(),*y = createNode();
      x->value = -3000;y->value = 3000;
      x->right = y;
      y->left = x;
      struct node* j,*h;
      for(h = head; h!=NULL; h = h->right){
        if(h->value == 3000)break;
      }
      j = h;
      x->down = head;
      head->up = x;
      y->down = j;
      j->up = y;
      head = x;
    }
    void insert(int x){
      struct node* r = createNode();
      r->value = x;
      struct node* e = head;
      while(e->down != NULL){
          if(e->value <= x){
            e = e->right;
          }
          else{
            e = e->left;
            e = e->down;
          }
      }
      while(e->value != 3000){
        if(e->value < x){
          e = e->right;
        }
        else{
          break;
        }
      }
      e = e->left;

      insertN(e,r);
      cout << ":P" << endl;
      /*r->right = e->right;
      r->left = e->right->left;
      e->right->left = r;
      e->right = r;
      */
      int i = coinflip(),headcount =0;
      if(i == 2){
        headcount++;
        struct node*p  =e->right;
        while(i != 1 && headcount < 6){
          struct node* t = createNode();
          t->value = x;
          struct node*y = p;
          while(p->up == NULL && p->value != -3000){
            cout << "Yup "<< endl;
            p = p->left;
          }
          if(p->value == -3000){
            if(p->up == NULL){cout << "Yuppie"<< endl;/*createNewLevel()*/p = p->up;insertN(p,t);t->down = y;y->up = t;i = coinflip();if(i == 2)headcount++;p = t;}
            /*else{
              p = p->up;
              insertN(p,t);
              t->down = y;
              y->up = t;
              i = coinflip();
              p = t;
            }*/
          }
          else{cout << "Yuppie1"<< endl;p = p->up;insertN(p,t);t->down = y;y->up = t;i = coinflip();if(i == 2)headcount++;p = t;}
        }
      }
    }

    void search(int x){
      struct node* u = head->right;
      while(1){
        if(u->value < x){
          u = u->right;
        }
        else if(u->value == x){
          cout << "Present" << endl;
          return;
        }

        else if(u->value == 3000 || u->value > x){
          if(u->down == NULL){
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

    struct node* search1(int x){
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
        while(y->value != 3000){
          cout << y->value << " ";
          y = y->right;
        }
        cout << endl;i++;u = u->down;
      }
    }
    void deleteN(struct node* a){
      a->left->right = a->right;
      a->right->left = a->left;
      if(a->down != NULL)a->down->up = NULL;
      free(a);
    }

    void restore(){
      struct node* a = head;
      while(a->right->value == 3000 && a->down != NULL){
        struct node * s = a->down;
        free(a->right);
        free(a);
        a = s;
      }
      head = a;
    }

    struct node* getHead(){return head;}

    void del(int x){
      struct node* t = search1(x);
      if(t != NULL){
      while(1){
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
  srand((unsigned)time(NULL));

  int n,x;
  skiplist slits(5);
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
          /*if(slits.getHead()->down != NULL)
          slits.restore();*/
          break;

      default:
        return 0;
    }
  }

}
