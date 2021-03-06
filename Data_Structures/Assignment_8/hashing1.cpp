/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 8
  Problem 1:- Implementing hashing using link list
  */
#include<iostream>
#include<stdlib.h>
using namespace std;

struct node{                                                    //structure node for hashing purposes
  int value;
  struct node* next;
  struct node* prev;
};

int hashFunction(int x){                                        //Defining hash function(The array is of size 5)
  return x%5;
}

class hashLinkList{                                             //declaring hashed link list class
  private:
    struct node*table[5];
    struct node*head[5];


  public:
    hashLinkList(){                                             //constructor for initializing the object
      for(int i  = 0; i < 5; i++){
        table[i]  = NULL;
        head[i] = NULL;
      }
    }

    struct node* createNode(){                                  //function to create a node
      struct node* x = (struct node*)new node;
      x->value = -10000;
      x->next = NULL;
      x->prev = NULL;
      return x;
    }

    int hashFunction(int x){                                    //
      return x%5;
    }

    void insert(int a){                                         //function to insert a value in the hashed link list
      int x = hashFunction(a);
      if(table[x] == NULL){
        table[x] = createNode();
        table[x]->value = a;
        head[x] = table[x];
      }
      else{
        struct node* g;
        for(struct node* r = table[x]; r!=NULL; r = r->next){
          if(r->next == NULL){
            g = r;
          }
          }

          struct node*p = createNode();
          g->next = p;
          p->prev = g;
          p->value = a;

      }
    }

    void display(){                                             //function to display the hashed link list
      for(int i = 0; i<5;i++){
        cout<<"index "<<i<<":- ";
        if(table[i] == NULL){
          cout<<"No Elements present"<<endl;
        }
        else{
          for(struct node*r = table[i];r!= NULL;r = r->next){
            cout<<r->value<<" ";
          }
          cout <<endl;
        }
      }
    }

    struct node* search(int x){                                 //function to search an element in the hashed link list
      int a = hashFunction(x),p=0;
      struct node*o;
      for(struct node*r = table[a];r!=NULL;r = r->next){
        if(r->value == x){
          p = 1;o = r;cout << "Present"<<endl;
          break;
        }
      }
      if(p == 0){
        cout << "Absent" << endl;
        return NULL;
      }
      return o;
    }

    void del(int x){                                            //function to delelte an element in the hashed link list
      struct node*b = search(x);
      struct node*a = b;
      for(int i = 0; i < 5; i++){
        if(head[i] == b){
          head[i] = table[i]->next;
          table[i] = table[i]->next;
          break;
        }
      }
      if(a == NULL){
        cout << "Element not present to be deleted" << endl;
      }
      else{
        if(a->prev == NULL)  a = a->next;
        if(a->prev != NULL)(a->prev)->next = a->next;

        //  cout << "Hi"<<endl;
         if(a->next != NULL)(a->next)->prev = a->prev;
        //else a = a->prev;
        free(b);
      }
    }

};

int main(){
  int n,x;
  hashLinkList hll;
  while(1){
    cout<<"***Menu***\n1.insert\n2.display\n3.search\n4.delete"<<endl;
    cin >>n;
    switch (n) {
      case 1:
      cin>>x;
      hll.insert(x);
      break;

      case 2:
      hll.display();
      break;

      case 3:
      cin >> x;
      hll.search(x);
      break;

      case 4:
      cin >> x;
      hll.del(x);
      break;

      default:
      return 0;
    }
  }
}
