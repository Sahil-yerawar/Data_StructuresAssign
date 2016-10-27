/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 2
  Problem 1:- Implementing Linkedlist of students
  Problem 2:- Implementing Queue of students using linkedlists
  */

#include<iostream>
#include<string>

using namespace std;

struct node{                            // Defining a node definition
  string roll_no;
  string name;
  string gender;
  int age;
  struct node* ptr;
};

class linklist{                         // Declaring the linklist class
  private:
    struct node* head;
    struct node* tail;

  public:
    linklist(){                         // constructor for the class
      head = NULL;
      tail = NULL;
    }
    struct node *list_search(string roll){    // Function to search the node from roll number
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
      if(list_search(roll) == NULL){        // Inserting a node in the linklist
      if(head == tail && head == NULL){
        head = x;
        tail = x;
      }
      else if(head == tail){
        head ->ptr = x;
        tail = x;

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
      else{
        cout << "Duplicate element present" << endl;
      }
      }
    void insertEnd(struct node* x){                   // Insertion at the end(Similar to enqueue of queue)
          if(tail == NULL){
            head = x;
            tail = x;
          }
          else{
            tail->ptr = x;
            tail = x;
          }
        }


        void delBegin(){                              // Deletion at the beginning(similar to dequeue of queue)
          if(head == NULL){
            cout << "The queue is empty!" << endl;
            return;
          }
          else{
            struct node *l = head->ptr;

            head = l;

          }
        }
    void del(string roll){                            // Deletion of a node from its roll number
      if(head == tail && head == NULL){
        cout << "Nothing to empty" << endl;
        return;
      }
      if(head == tail && tail->roll_no  == roll){
        head = NULL;
        tail = NULL;
        return;
      }
      if(list_search(roll) == NULL){ // ToDo:- make function distinguish between start, end and middle node
        cout << "The element to be deleted is not present" << endl;
        return;
      }else{
        if(head->roll_no == roll){
          head = head->ptr;
        }else{
      struct node *prev_node;
      for(struct node* i = head; i != NULL; i= i->ptr){
        if((i->ptr)->roll_no == roll ){
          prev_node = i;
          break;
        }
      }

      prev_node ->ptr = (prev_node->ptr)->ptr;
      }
    }
  }
  struct node* createNode(){                            // Function to create a node
    struct node* x = (struct node*)new node;
    return x;
  }
  void traverse(){                                      // Traversing a linklist
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
  void printnode(struct node *x){                     // Printing a node
    cout << "(" << x->roll_no << "," << x->name << "," << x->age << "," << x->gender << ")";
  }
  void remove_duplicate(){                            // removing the duplicates
    for(struct node *i = head; i != NULL; i = i->ptr){
      for(struct node *j = i->ptr; j != NULL; j = j->ptr){
        if((i->roll_no).compare(j->roll_no) == 0){
          del(j->roll_no);
        }
      }
    }
  }
};

int main(){
    int choice;
    cout << "Choice of implementation\n1.Normal\n2.queue" << endl;
    cin >> choice;
    linklist link;
    int n;
    string i;
    if(!(choice-1)){
    while(1){
      cout << "***Menu***\n1.insert\n2.delete\n3.traverse\n4.remove duplicate" << endl;
      cin >> n;
      switch (n) {
        case 1:{
        cout << "Enter roll no,name,age,gender" << endl;
        struct node* x = link.createNode();
        cin >> x->roll_no >> x->name >> x->age >> x->gender;
        cout << "Enter the roll_no to be put after" << endl;
        cin >> i;
        link.insert(x,i);
        break;}

        case 2:{
        cout << "Enter the roll_no to be put after" << endl;
        cin >> i;
        link.del(i);
        break;}

        case 3:
        link.traverse();
        break;

        case 4:
        link.remove_duplicate();
        break;

        default:
        return 0;
      }
    }
}
else{
  while(1){
    cout << "***Menu***\n1.insert\n2.delete\n3.traverse\n4.remove_duplicate" << endl;
    cin >> n;
    switch (n) {
      case 1:{
      cout << "Enter roll no,name,age,gender" << endl;
      struct node* x = link.createNode();
      cin >> x->roll_no >> x->name >> x->age >> x->gender;
      /*cout << "Enter the roll_no to be put after" << endl;
      cin >> i;*/
      link.insertEnd(x);
      break;}

      case 2:{
      /*cout << "Enter the roll_no to be put after" << endl;
      cin >> i;*/
      link.delBegin();
      break;}

      case 3:
      link.traverse();
      break;


      case 4:
      link.remove_duplicate();
      break;

      default:
      return 0;
    }
  }
}
}
