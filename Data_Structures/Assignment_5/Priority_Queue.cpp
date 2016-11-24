/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 5

  Problem 2:- Implementing minimum priority queue
*/

#include<iostream>
using namespace std;
    /*Defining a class of min-heap(we define the heap to have a size of 15 for now)*/
class min_heap{
  private:
    int *queue;                           // DEFINING the three importan  t fields, the array, the length and the
    int heapsize;                         // heap size. Note:- heapsize <= length.
    int length;

  public:
    min_heap(int a[],int x){              // constructor for the class
       queue = a;
       heapsize = x;
       length = 15;
    }

    int parent(int i){                    //Determining the parent of a node(i starts from 1)
      return i/2;
    }
    int left(int i){                      //Determining the left child  of a node(i starts from 1)
      return 2*i;
    }
    int right(int i){                     //Determining the right child of a node(i starts from 1)
      return 2*i + 1;
    }
    void heapify(int i){                  //It tries to put the considered element in the appropriate position.
                                          //Here also i starts from 1
        int l = left(i),largest;          // Determining the left and right child
        int r = right(i);

        /*Determining among the node, its left child and its right child, the greatest of the three*/
        if( l <= heapsize && queue[l-1]< queue[i-1]){
          largest = l-1;
        }
        else largest = i-1;
        if(r <=heapsize && queue[r-1] < queue[largest]){
          largest = r-1;

        }
        /*If the largest is one of the children, we swap it with the considered node and heapify the so-called 'largest' node*/

        if (largest != i-1){
          int temp = queue[i-1];
          queue[i-1] = queue[largest];
          queue[largest] = temp;
          heapify(largest+1);
        }


    }

    int *getQueue(){                       //helper function to get array
      return this->queue;
    }
    void build_heap(){                     //constructs min-heap from the array
      //heapsize = length;
      for(int i = heapsize/2; i > 0; i--){
        heapify(i);
      }
    }
    int heap_min(){                           //returns min element
      return queue[0];
    }

    int heap_remove_min(){                    // removes the minimum element and returns it
      if(heapsize < 1) return -1;
      int min = queue[0];
      queue[0] = queue[heapsize-1];
      heapsize--;
      heapify(1);
      return min;
    }
    int heap_inc_value(int i, int k){         // Increases the value of a particular node and puts it in correct position
      if(k < queue[i-1]) return -1;
      queue[i-1] = k;
      while(i>1 && queue[parent(i)-1] < queue[i-1]){
        int temp = queue[parent(i)-1];
        queue[parent(i)-1] = queue[i-1];
        queue[i-1] = temp;
        i = parent(i);
      }

    }
    void heap_insert(int i){                  // Inserts a new integer into the heap and puts it in correct position(provided space exists)
      heapsize++;
      queue[heapsize-1] = -10;
      heap_inc_value(heapsize,i);
    }
    int getHeapsize(){
      return heapsize;
    }

};


int main(){
  int array[15] = {0},count;
  cout << "Enter 15 elements for the heap"<<endl; // filling the array first
  for(int i = 0; i < 15; i++){
    cin >> array[i];
  }
  min_heap heap(array,15);                        // declaring the min-heap class
  int h,g,m;
  while(1){                                       // Menu for modifying the heap
    cout << "***Menu***\n1.Build a min heap\n2.Priority Queue- get minimum\n3.Priority Queue- Remove minimum\n4.Priority Queue- Insert a value\n" << endl;
    cin >> h;
    switch (h) {
      case 1:
      heap.build_heap();

      for(int i = 0; i < heap.getHeapsize(); i++){
        cout<<(heap.getQueue())[i] << " ";
      }
      cout << endl;
      break;

      /*case 2:
      heap.heapsort();
      for(int i = 0; i < heap.getHeapsize(); i++){
        cout<<(heap.getQueue())[i]<< " ";
      }
      cout << endl;
      break;
      */

      case 2:
      heap.build_heap();
      cout << heap.heap_min() << endl;
      break;

      case 3:
      heap.build_heap();
      m = heap.heap_remove_min();
      if(m != -1){
      cout << "The element removed is " << m << endl;
      heap.build_heap();
      for(int i = 0; i < heap.getHeapsize(); i++){
        cout<<(heap.getQueue())[i]<< " ";
      }
      cout << endl;}
      else cout << "Heap underflow" << endl;
      break;

      case 4:
      heap.build_heap();
      cout << "Enter the positive integer to be added" << endl;
      cin >> g;
      heap.heap_insert(g);
      heap.build_heap();
      for(int i = 0; i < heap.getHeapsize(); i++){
        cout<<(heap.getQueue())[i]<< " ";
      }
      cout << endl;
      break;

      default:
      return 0;


    }
  }
}
