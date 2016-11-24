/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 5
  Problem :- Finding the minimum spanning tree of a given graph using prim's algorithm
*/
#include<iostream>
using namespace std;


struct node{                                                    //declaring a node of the graph
  int val;
  int weight;
  int key;
  int parent;
  struct node* ptr;
};

class max_heap{
  private:
    struct node**queue;                               // DEFINING the three importamt fields, the array, the length and the
    int heapsize;                                     // heap size. Note:- heapsize <= length.
    int length;

  public:
    max_heap(struct node* a[],int x){                           // constructor for the class
       queue = a;
       heapsize = x;
       length = x;
    }

    int parent(int i){                                          //Determining the parent of a node(i starts from 1)
      return i/2;
    }
    int left(int i){                                            //Determining the left child  of a node(i starts from 1)
      return 2*i;
    }
    int right(int i){                                           //Determining the right child of a node(i starts from 1)
      return 2*i + 1;
    }
    void heapify(int i){                                        //It tries to put the considered element in the appropriate position.
                                          //Here also i starts from 1
        int l = left(i),largest;          // Determining the left and right child
        int r = right(i);

        /*Determining among the node, its left child and its right child, the greatest of the three*/
        if( l <= heapsize && queue[l-1]->key< queue[i-1]->key){
          largest = l-1;
        }
        else largest = i-1;
        if(r <=heapsize && queue[r-1]->key < queue[largest]->key){
          largest = r-1;

        }
        /*If the largest is one of the children, we swap it with the considered node and heapify the so-called 'largest' node*/

        if (largest != i-1){
          struct node* temp = queue[i-1];
          queue[i-1] = queue[largest];
          queue[largest] = temp;
          heapify(largest+1);
        }


    }

    struct node**getQueue(){                                    //helper function to get array
      return this->queue;
    }
    void build_heap(){                                          //constructs max-heap from the array
      //heapsize = length;
      for(int i = heapsize/2; i > 0; i--){
        heapify(i);
      }
    }
    void heapsort() {                       //Uses max heap to sort the array
      build_heap();
      int i = length;
      int q = heapsize;
      while(i > 1){

        struct node* temp = queue[i-1];
        queue[i-1] = queue[0];
        queue[0] = temp;
        heapsize--;
        heapify(1);
        i--;
      }
      heapsize = q;
    }

    struct node* heap_max(){                           //returns max element
      return queue[0];
    }

    struct node* heap_remove_max(){                    // removes the maximum element and returns it
      if(heapsize < 1) return NULL;
      struct node* max = queue[0];
      queue[0] = queue[heapsize-1];
      heapsize--;
      heapify(1);
      return max;
    }
    int heap_inc_value(int i, int k){         // Increases the value of a particular node and puts it in correct position
      if(k < queue[i-1]->val) return -1;
      queue[i-1]->val = k;
      while(i>1 && queue[parent(i)-1] < queue[i-1]){
        struct node* temp = queue[parent(i)-1];
        queue[parent(i)-1] = queue[i-1];
        queue[i-1] = temp;
        i = parent(i);
      }

    }
    void heap_insert(int i){                  // Inserts a new integer into the heap and puts it in correct position(provided space exists)
      heapsize++;
      queue[heapsize-1]->val = -10;
      heap_inc_value(heapsize,i);
    }
    int getHeapsize(){
      return heapsize;
    }

};


struct node**vertices,**vertices1;                              //declaring a set of vertices

class graph{                                                    //declring a class of a graph
  private:
     struct node**array;
     int edgeCount;
  public:
    graph(struct node*x[]){                                     //constructor for graph object
      array = x;
      edgeCount = 0;
    }
    struct node* b;
    void addEdge(struct node* arr[2]){                          //function to add an edge in the graph
      if(checkEdge(arr) == -1){
      for(struct node* a = this->array[(arr[0]->val)-1]; a != NULL; a = a->ptr){
        if(a->ptr == NULL){
          b = a;
          break;
        }
      }
      b->ptr = arr[1];

        for(struct node* a = this->array[(arr[1]->val)-1]; a != NULL; a = a->ptr){
          if(a->ptr == NULL){
            b = a;
            break;
          }
        }
        b->ptr = arr[0];
      edgeCount++;}
          else{
            cout << "Edge already exists" << endl;
          }
    }
    void deleteEdge(struct node* arr[2]){                       //function to delete an edge in the graph
      if(checkEdge(arr) == 1){
        cout << "boo" << endl;
        for(struct node* a = this->array[(arr[0]->val)-1]; a != NULL; a = a->ptr){
          cout << "boo" << endl;
          if((a->ptr)->val == arr[1]->val){
            struct node* b = a->ptr;
            a->ptr = b->ptr;
            b->ptr = NULL;
            delete b;
            break;
          }
        }



          for(struct node* a = this->array[(arr[1]->val)-1]; a != NULL; a = a->ptr){
            if((a->ptr)->val == arr[0]->val){
              cout << "boo" << endl;
              struct node* b = a->ptr;
              a->ptr = b->ptr;
              b->ptr = NULL;
              delete b;
              break;
            }
          }
          edgeCount--;

          }
          else{
            cout << "The edge not found" << endl;
          }
        }


    struct node* createNode(int x,int y){                       //function to create a node
      struct node* f = (struct node*)new node;
      f->val = x;
      f->weight = y;
      f->key = 10000;
      f->parent = 0;
      f->ptr = NULL;

    }
    struct node ** getvertices(){                               //function to get the list of vertices
      return array;
    }
    int checkEdge(struct node* arr[2]){                         //function to check whether the edge exists or not

      for(struct node* a = this->array[(arr[1]->val)-1]; a != NULL; a = a->ptr){
                if(a->val  == arr[0]->val){
                  return 1;

                }
              }
              return -1;
    }

    int getEdgeCount(){                                         //function which returns the number of edges
      return edgeCount;
    }
    void changeEdgeCount(int x){                                //function to change the edgeCount
      edgeCount = x;
    }

};

int main(){
  int x;
  cout << "Enter the number of vertices of the graph" << endl;
  cin >> x;
  vertices = new struct node*[x];
  vertices1 = new struct node*[x];
  graph g(vertices);                                            //declaring two graphs, one for input of values and other for get the mst from the first one
  graph circle(vertices1);
  struct node* queue[x];
  for(int i = 0; i < x; i++){
    struct node* p = g.createNode(0,0);
    g.getvertices()[i] = p;
    struct node* q  = g.createNode(0,0);
    circle.getvertices()[i] = q;
    queue[i] = p;
    queue[i]->val = i+1;
  }
  queue[0]->key = 0;
  int n,a,b,c,idx = 0,p=0;
  struct node* edge[2];
  while(1){
    if(p == 1)break;
    cout << "***menu***\n1.AddEdge\n2.Display list\n3.deleteEdge\n4.Exit and find MST"<< endl;
    cin >> n;
    switch (n) {
      case 1:
      cout << "Enter the source vertex, then destination vertex to be added and the weight" << endl;
      cin >> a >> b >> c;
      if(a <= 0 || b <= 0 || c < 0){
        cout<<"Sorry, negative numbered and zero vertices and negative weights are not accpetable here!"<<endl;
        break;
      }
      edge[0] = g.createNode(a,c);
      edge[1] = g.createNode(b,c);
      g.addEdge(edge);
      break;

      case 2:
      for(int i = 0; i < x; i++){
        cout << "1st order relatives of " << i+1 << ":- " << endl;
        for(struct node* boo = g.getvertices()[i]; boo != NULL; boo = boo->ptr ){
          cout << boo->val <<"(" << boo->weight << ")"<<" " ;
        }
        cout << endl;
      }
      break;


      case 3:
      cout << "Enter the source vertex, then destination vertex to be added and the weight" << endl;
      cin >> a >> b >> c;
      edge[0] = g.createNode(a,c);
      edge[1] = g.createNode(b,c);
       g.deleteEdge(edge);
      break;

      case 4:
      idx = g.getEdgeCount();
      p = 1;
      break;

      default:
      return 0;

    }
  }


  max_heap heap(queue,x);                                       //building a heap of the edges
  heap.build_heap();                                            //calling build heap



  while(heap.getHeapsize() != 0){                               //prim's algorithm to select the edges of the MST
    struct node*u = heap.heap_remove_max();
    if(u->parent != 0){
      struct node * edge[2];
      edge[0] = circle.createNode(u->val,u->key);
      edge[1] = circle.createNode(u->parent,u->key);
      circle.addEdge(edge);
    }

      for(struct node*i = g.getvertices()[u->val-1]->ptr; i!= NULL; i = i->ptr){
        int p = 0,r;
        for(int j = 0; j < heap.getHeapsize(); j++){
    if(heap.getQueue()[j]->val == i->val){
            p = 1;
            r = j;
            break;
          }
        }
        if(p == 1){
          if(i->weight < heap.getQueue()[r]->key){
            heap.getQueue()[r]->parent = u->val;
            heap.getQueue()[r]->key = i->weight;
          }
        }

      }

      //heap.heapify(1);
      heap.build_heap();
  }




  for(int i = 0; i < x; i++){                                   //printing the MST
    cout << "1st order relatives of " << i+1 << ":- " << endl;
    for(struct node* boo = circle.getvertices()[i]; boo != NULL; boo = boo->ptr ){
      cout << boo->val <<"(" << boo->weight << ")"<<" " ;
    }
    cout << endl;
  }
}
