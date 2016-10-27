/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 1
  Problem 6:- Implementing Stack using array
  */



#include<iostream>

using namespace std;

class stack{                                            // defining stack class
  private:
     int* arr;
     int ptr;
     int size;

  public:
     stack(int x){                                      //constructor for stack class
      arr = new int[x];
      ptr = 0;
      size = x;
    }

    void insert(int y){                                 // inserting at the end of the stack
      arr[ptr] = y;
      ptr++;
    }
    void del(){                                         // deletion of the element from the end of the stack
      if(ptr == 0){
        cout << "Stack is empty!" << endl;
      return;
      }else{
        ptr--;
      }


    }
    void traverse(){                                    // Traversing through the stack
      if(ptr == 0){
      cout << "Empty" << endl;
      return;
      }
      for(int i = 0; i < ptr; i++){
        cout << arr[i]  << " ";
      }
      cout << endl;

    }
    /*helper functions for getting index and dynamic size of the array*/
    int getPtr(){
      return ptr;
    }
    int getSize(){
      return size;
    }


};


int main(){
  int size;
  cout << "Enter the size of the stack you wish" << endl;
  cin >> size;
  stack pizza(size);                    //declaring & Initializing the pizza stack
  int n,x;
  while(1){
    cout << "***Menu***\n1.insert\n2.delete\n3.traverse\n4.exit" << endl;
    cin >> n;
    switch (n) {
      case 1:
      if(pizza.getPtr() == pizza.getSize()){
        cout << "Stack is full!" << endl;

      }
      else{cout << "Enter the number to be put in stack" << endl;
      cin >> x;
      pizza.insert(x);}
      break;

      case 2:
      pizza.del();
      break;

      case 3:
      pizza.traverse();
      break;

      case 4:
      return 0;

     }
  }
}
