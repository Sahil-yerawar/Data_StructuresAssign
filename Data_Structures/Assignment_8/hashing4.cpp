#include<iostream>
using namespace std;



struct node{
  int value;
  int fillStatus;         //0 for purely empty, 1 for filled,2 for previously filled but empty now

};


class hashLinear{
  private:
    struct node*table[13];

  public:
    hashLinear(){
      for(int i = 0; i < 13;i++){
        table[i] = createNode();

      }

    }

    struct node* createNode(){
      struct node* x = (struct node*)new node();
      x->value = 0;
      x->fillStatus = 0;
    }
    int hashFunction(int x){
      return x%7;
    }
    int linearProb(int x,int i){
      return (hashFunction(x)+i*i)%13;
    }

    void insert(int x){
      int a = linearProb(x,0);
      if(table[a]->fillStatus == 0 || table[a]->fillStatus == 2){
        table[a]->value = x;table[a]->fillStatus = 1;
      }
      else{
        int i = 1,f = linearProb(x,i);
        while(f != a){
          if(table[f]->fillStatus != 1){
            table[f]->value = x;table[f]->fillStatus = 1;
            break;
          }
          else{
            cout << "Hi"<<endl;
            i++;
            f = linearProb(x,i);
          }

        }
      }
    }

    void display(){
      for(int i = 0; i < 13; i++){
        if(table[i]->fillStatus != 1){
        cout <<"Index "<< i << ":- "<< "No data present"<<endl;
      }
      else{
        cout <<"Index "<< i << ":- "<< table[i]->value<<endl;
      }
      }
    }

    int search(int x){
      int a = linearProb(x,0),p = 0;
      if(table[a]->fillStatus == 1 && table[a]->value == x){
        p = 1;return a;
      }
      else{
        int i = 1,f = linearProb(x,i);
        while(f != a){
          if(table[f]->value == x){
            p = 1;return f;
            break;
          }
          else{
            i += 1;
            f = linearProb(x,i);
          }
        }
        if(p == 0) return -1;
      }
    }

  void del(int x){
    int a = search(x);
    if(x != -1){
      table[a]->fillStatus = 2;
    }
    else{
      cout << "Element to be deleted is not found" << endl;
    }
  }
};

int main(){
  int n,x,y;
  hashLinear hll;
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
      //cout << y << endl;
      break;

      case 4:
      cin >> x;
       hll.del(x);
      //cout << y << endl;
      break;

      default:
      return 0;
    }
  }
}
