#include<iostream>
using namespace std;


struct element{
  int value;
  struct element* next,last;
};
int hashFunction(int x){
  return x%5;
}
int main(){
  int n,x;
  struct node*table[5];
  for(int i = 0; i < 5; i++){
    table[i] = NULL;
  }
  while(1){
    cout<<"***Menu***\n1.General Hashing using linked list\n2.Implementation Using Overflow Area\n3.Linear probing\n4.quadratic probing"<<endl;
    cin >> n;
    switch (n) {
      case 1:
      cout << "Enter the key" << endl;
      cin >> x;
      struct node*start = table[hashFunction(x)];
      if(start == NULL){
        struct element* a = (struct element*)new element;
        a->last = NULL;
        a->val =
      }
    }
  }
}
