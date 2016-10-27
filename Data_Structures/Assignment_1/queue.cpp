/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 1
  Problem 5:- Implementing a Circular Queue and its basic operations
  */
#include<iostream>
using namespace std;


#define SIZE 5
class queue{                                              //Defining a circular queue(hereafter mentioned queue for this pro) class with constant size 5
  private:                                                // Fields required to describe queue
    int *arr;
    int size;
    int front;
    int rear;

  public:
    queue(int x){                                         //Constructor for queue class
      arr = new int[x];
      size = x;
      front = 0;
      rear = 0;
    }
    void insert(int y){                                   // insertion of an element in queue
      if((rear - front) > size){
        cout << "Queue is full, please delete an element first" << endl;
        return;
      }
      arr[rear%size] = y;
      rear++;

    }
    void del(){                                           // Deletion of an element from the queue
      if(front == rear){
        cout << "Queue is empty! Please insert an element first"<< endl;
        return;
      }
      front++;

    }
    void traversal(){                                     // traversing through the circular queue
      if(front == rear) cout << "empty" << endl;
      for(int i = front; i < rear; i++){
        cout << arr[i%size] << " ";
      }
      cout << endl;
    }
    int getRear(){                                        //Helper functions for getting rear, front and size of the queue
      return rear;
    }
    int getFront(){
      return front;

    }
    int getSize(){
      return size;
    }
};

int main(){
  int size;
  cout << "Enter the size of the queue to be filled" << endl;
  cin >> size;
  queue Line(size);                                         //Initializing the new queue class with given size
  int n,x;
  while(1){                                                 //Interactive menu to handle queue by its operations
    cout << "*** Menu *** \n1.insert\n2.delete\n3.traversal\n4.exit" << endl;

    cin >> n;
    switch (n) {
      case 1:
      if(Line.getRear() - Line.getFront() == Line .getSize())                 // Checking exception for insert function first
      cout << "Queue is full, please delete an element first" << endl;
      else{cin >> x;
      Line.insert(x);} break;

      case 2:
      Line.del();break;

      case 3:
      Line.traversal();break;

      case 4:
      return 0;
    }
  }
}
