#include<iostream>
/*****Still pending****/
using namespace std;
struct node{
  int value;
  int presentStatus;
  int index;
};

class hashOverflow{
  private:
    struct node primaryTable[7];
    struct node overflowTable[7];

  public:
    hashOverflow(){
      for(int i = 0; i < 7; i++){
        primaryTable[i] = createNode();
        overflowTable[i] = createNode();
      }
    }

    struct node createNode(){
      struct node x = new node();
      x->value = -1;
      x->presentStatus = 0;
      x->index = -1;
      return x;
    }

    int hashFunction(int x){
      return x%7;
    }

    void insert(int x){
      int a = hashFunction(x);
      if(primaryTable[a]->presentStatus == 0){
        primaryTable[a]->value = x;
        primaryTable[a]->presentStatus = 1;
      }
      else{

      }
    }
};

int main(){

}
