#include<iostream>
#include<stdlib.h>
using namespace std;

struct node{
  int val;
  int weight;
  struct node* ptr;
};
class dSet{
  private:
    int* Parent;

  public:
    dSet(int arr[]){
      Parent =arr;
    }

   int Find(int i) {            //i in 0 starting

    // If i is the parent of itself
    if (Parent[i] == i) {

        // Then i is the representative of his set
        return i;
    }
    else { // Else if i is not the parent of itself

        // Then i is not the representative of his set,
        // so we recursively call Find on its parent
        return Find(Parent[i]);
    }
}
void Union(int i, int j) {

  // Find the representatives (or the root nodes) for the set that includes i
  int irep = this->Find(i),
      // And do the same for the set that includes j
      jrep = this->Find(j);

  // Make the parent of i's representative be j's representative
  // (effectively moving all of i's set into j's set)
  this->Parent[irep] = jrep;
}
};

void insertSort(int a[200][3],int size){
  for(int j = 0; j < size; j++){
  for(int i = 0; i < size-1; i++){
    if(a[i+1][2] < a[i][2]){                  //whenever an element is lesser than the element behind it, it shifts back
      int j = i+1;                      // till it finds an element greater than the considered element , at which it stops.
      int val = a[j][2];
      int val1 = a[j][1];
      int val2 = a[j][0];
      while(j >  0 && a[j][2] < a[j-1][2]){   // while loop used till we find a greater element
	//int temp = a[j];
	a[j][2] = a[j-1][2];
  a[j][1] = a[j-1][1];
  a[j][0] = a[j-1][0];
	//a[j-1] = temp;
	j--;
      }
      a[j][2] = val;
      a[j][1] = val1;
      a[j][0] = val2;                       // When it finds the element, it does final swapping  so that it is placed in order.
    }
  }
}/*
  cout << "The sorted array is:- " << endl;
  for(int j = 0; j < size; j++){        // Printing of array within the program
    cout << a[j] << " " ;}
  cout << endl;*/
}

 struct node**vertices;
class graph{
  private:
     struct node**array;
     int edgeCount;
  public:
    graph(struct node*x[]){
      array = x;
      edgeCount = 0;
    }
    struct node* b;
    void addEdge(struct node* arr[2]){
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
    void deleteEdge(struct node* arr[2]){
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

        //b->ptr = arr[1];

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
          //b->ptr = arr[0];
          }
          else{
            cout << "The edge not found" << endl;
          }
        }


    struct node* createNode(int x,int y){
      struct node* f = (struct node*)new node;
      f->val = x;
      f->weight = y;
      f->ptr = NULL;

    }
    struct node ** getvertices(){
      return array;
    }
    int checkEdge(struct node* arr[2]){

      for(struct node* a = this->array[(arr[1]->val)-1]; a != NULL; a = a->ptr){
                if(a->val  == arr[0]->val){
                  return 1;

                }
              }
              return -1;
    }

    int getEdgeCount(){
      return edgeCount;
    }
    void changeEdgeCount(int x){
      edgeCount = x;
    }

};

int main(){
  int x;
  cout << "Enter the number of vertices of the graph" << endl;
  cin >> x;
  vertices = new struct node*[x];
  graph g(vertices);
  //int edgeQueue[][3]

  for(int i = 0; i < x; i++){
    struct node* p = g.createNode(0,0);
    g.getvertices()[i] = p;
  }
  int n,a,b,c,idx = 0,p;
  struct node* edge[2];
  while(1){
    if(p == 1)break;
    cout << "***menu***\n1.AddEdge\n2.Display list\n3.deleteEdge\n4.make Edge list"<< endl;
    cin >> n;
    switch (n) {
      case 1:
      cout << "Enter the source vertex, then destination vertex to be added and the weight" << endl;
      cin >> a >> b >> c;
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

cout << idx << endl;
int edgeSet[idx][3],ad;

struct node* edg[2];
if(idx != 0){
  int q = 0;
  for(int i = 0; i < x; i++){
    if((g.getvertices()[i])->ptr != NULL){
      cout << "boob" << endl;
    for(struct node*s = (g.getvertices()[i])->ptr; s != NULL; s = s->ptr){
      //cout << "boo" << endl;
      /*int w = 0;
      for(int j = 0; j < q+1; j++){
        if(edgeSet[q][0] ==  s->val){w = 1;break;}
      }*/
      if(i+1 < s->val){
      edgeSet[q][0] = i+1;
      edgeSet[q][1] = s->val;
      edgeSet[q][2] = s->weight;
      q++;

      /*edg[0] = g.createNode(i+1,s->weight);
      edg[1] = s;
      struct node*q = s;
      cout << "boo" << endl;
      g.deleteEdge(edg);
      s = q;*/
      cout << "boo" << endl;
      /*int doof = g.getEdgeCount();
      doof--;
      g.changeEdgeCount(doof);*/
    }
    else{
      cout << ":P" << endl;
      continue;
    }
    }

  }
  else {cout << "-.-" <<endl;}

}
  ad = q;}

for(int i = 0; i < ad; i++){
  cout << "(" << edgeSet[i][0] << "," << edgeSet[i][1] <<"," << edgeSet[i][2] << ")" << " ";
}


insertSort(edgeSet,idx);
for(int i = 0; i < ad; i++){
  cout << "(" << edgeSet[i][0] << "," << edgeSet[i][1] <<"," << edgeSet[i][2] << ")" << " ";
}

cout << endl;
int DSet[x];
for(int i = 0; i < x; i++){
  DSet[i] = i;
}
dSet depc(DSet);
for(int i = 0; i < ad; i++){
  if(depc.Find(edgeSet[i][0]-1) != depc.Find(edgeSet[i][1]-1)){
    //dSet[edgeSet[i][1]-1] = dSet[edgeSet[i][0]-1];
    cout << "(" << edgeSet[i][0] << "," << edgeSet[i][1] <<"," << edgeSet[i][2] << ")" << " ";
    depc.Union(edgeSet[i][0]-1,edgeSet[i][1]-1);
  }
/*  else{
    edgeSet[i][0] = 0;
    edgeSet[i][1] = 0;
    edgeSet[i][2] = 0;
  }*/
}
cout << endl;/*
for(int i = 0; i < ad; i++){
  cout << "(" << edgeSet[i][0] << "," << edgeSet[i][1] <<"," << edgeSet[i][2] << ")" << " ";
}*/



return 2;

}