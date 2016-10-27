/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 2
  Problem 1:- Implementing Linkedlist of students
  */




#include<iostream>

using namespace std;

class linklist{
  private:
    struct node* head;
    struct node* tail;

  public:
    linklist(){
      head = NULL;
      tail = NULL;
    }
    struct node *list_search(string roll){
      struct node *p = head,*c;
      while(p != NULL){
        if(p->roll_no == roll){
          c = p;
          return c;
        }
        p = p->ptr;
      }
      if(p == NULL)return p;
    }
    void insert(struct node *x,string roll){
      if(head == tail && head == NULL){
        head = x;
        tail = x;
      }
      else if(head == tail){
        head ->ptr = x;
        tail = x;
        //cout << "The linklist is empty" << endl;
        return;
      }
      else{
        struct node*p = list_search(roll);
        if(p == NULL){
          cout << "Not found the element to insert after" << endl;

          return;
        }
        else{
          x->ptr = p->ptr;
          p->ptr = x;
        }

          }
        }
    void insertEnd(struct node* x){
      if(tail == NULL){
        head = x;
        tail = x;
      }
      else{
        tail->ptr = x;
        tail = x;
      }
    }

    void delBegin(){
      if(head == NULL){
        cout << "The queue is empty!" << endl;
        return;
      }
      else{
        struct node *l = head->ptr;
        free(head);
        head = l;

      }
    }


    void del(string roll){
      if(head == tail && head == NULL){
        cout << "Nothing to empty" << endl;
      }
      if(list_search(roll) == NULL){
        cout << "The element to be deleted is not present" << endl;
        return;
      }else{
      struct node *prev_node;
      for(struct node* i = head; i != NULL; i= i->ptr){
        if((i->ptr)->roll_no == roll){
          prev_node = i;
          break;
        }
      }
      prev_node->ptr = NULL;
      prev_node -> ptr = (prev_node->ptr)->ptr;

    }
  }
  struct node* createNode(){
    struct node* x = (struct node*)new node;
    return x;
  }
  void traverse(){
    if(head == tail && tail == NULL){
      cout << " Empty"  << endl;
      return;
    }
    else if(head == tail){
      printnode(head);
    }
    else{
      for(struct node * i = head; i != NULL; i = i->ptr){
        if(i->ptr != NULL){printnode(i);
        cout << "--->";
      }
      else{
        printnode(i);
      }
    }
      cout << endl;
    }
  }
  void printnode(struct node *x){
    cout << "(" << x->roll_no << "," << x->name << "," << x->age << "," << x->gender << ")";
  }
};

int main(){
  linklist queue;
  int n,x;
  string i;
  while(1){
    cout << "***Menu***\n1.insert\n2.delete\n3.traverse" << endl;
    cin >> n;
    switch (n) {
      case 1:{
      cout << "Enter roll no,name,age,gender" << endl;
      struct node* x = queue.createNode();
      cin >> x->roll_no >> x->name >> x->age >> x->gender;
      /*cout << "Enter the roll_no to be put after" << endl;
      cin >> i;*/
      queue.insertEnd(x);
      break;}

      case 2:{
      /*cout << "Enter the roll_no to be put after" << endl;
      cin >> i;*/
      queue.delBegin();
      break;}

      case 3:
      queue.traverse();
      break;

      default:
      return 0;
    }
  }
}
