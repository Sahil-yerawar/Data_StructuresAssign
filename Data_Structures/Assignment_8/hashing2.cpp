/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 5
  Problem 2:- Implementing hashing using overflow area
*/

/* the table size is seven(7)*/
#include<iostream>
using namespace std;
struct node{                                                    //defining the node for the table
  int value;
  int presentStatus;                                  //0 for empty, 1 for filled
  int index;                                          //contains the address(in index format) of the next chained node
};

class hashOverflow{                                             //defining the hashtable using overflow area
  private:
    struct node* primaryTable[7];
    struct node* overflowTable[7];

  public:
    hashOverflow(){                                             //constructor to initialize the object
      for(int i = 0; i < 7; i++){
        primaryTable[i] = createNode();
        overflowTable[i] = createNode();
      }
    }

    struct node* createNode(){                                  //function to create a node
      struct node* x =(struct node*) new node();
      x->value = -1;
      x->presentStatus = 0;
      x->index = -1;
      return x;
    }

    int hashFunction(int x){                                    //hash function to be used in hashing
      return x%7;
    }

    void insert(int x){
      if(search1(x) == 1)cout<<"The element is already present in the hash table"<<endl;
      else{//function to insert a value in the hash table
      int a = hashFunction(x);
      if(primaryTable[a]->presentStatus == 0){        //if the primary table slotis itself empty
        primaryTable[a]->value = x;
        primaryTable[a]->presentStatus = 1;
      }
      else{

          if(overflowTable[a]->presentStatus == 0){   //if the corresponding overflow slot is empty
            overflowTable[a]->value = x;
            overflowTable[a]->presentStatus = 1;
            primaryTable[a]->index = a;
            //break;
          }
          else{
            /*if(a+1 == 7)cout<<"Sorry, The overflowtable is full"<<endl;
            else{
              int i,isEmpty=0;
              for(i = a+1;i < 7;i++){
                if(overflowTable[i]->presentStatus == 0){
                  isEmpty = 1;
                  break;}
              }
              if(isEmpty == 1){
              overflowTable[i]->value = x;
              overflowTable[i]->presentStatus = 1;
              overflowTable[a]->index = i;
            }
              else{
                cout<<"Sorry, The overflowtable is full"<<endl;
              }
            }*/
            if(primaryTable[a]->index == -1){
              int i,isEmpty=0;
              for(int i =0; i < 7; i++){
                if(overflowTable[i]->presentStatus == 0){
                  isEmpty = 1;
                  break;
                }
              }
              if(isEmpty == 1){
                overflowTable[i]->value = x;
                overflowTable[i]->presentStatus = 1;
                primaryTable[a]->index = i;
              }
              else cout<<"Sorry, Theoverflow table is empty" << endl;
            }
            else {
              int f = primaryTable[a]->index;
              while(overflowTable[f]->index != -1){
                f = overflowTable[f]->index;
              }
              if(f+1 == 7)cout<<"Sorry, the overflowTable is empty"<<endl;
              else{
                int i,isEmpty;
                for(i = f+1;i<7;i++){
                  if(overflowTable[i]->presentStatus == 0){
                    isEmpty = 1;
                    break;
                  }
                }
                if(isEmpty == 1){
                  overflowTable[i]->value = x;
                  overflowTable[i]->presentStatus = 1;
                  overflowTable[f]->index = i;
                }
              }
            }
            }


      }
    }
    }
    void search(int x){                                         //function to check whether the value is present or not
      int a = hashFunction(x);
      if(primaryTable[a]->value == x)cout << "Present"<<endl;
      else if(primaryTable[a]->index == -1)cout << "absent" << endl;
      else{
        while(1){
          if(overflowTable[a]->value == x){
            cout <<"present"<<endl;
            break;
          }
          else if(overflowTable[a]->index == -1){
            cout << "absent1"<<endl;
            break;
          }
          else{
            a = overflowTable[a]->index;
          }
        }
      }
    }

    int search1(int x){
      int a = hashFunction(x);
      if(primaryTable[a]->value == x)return 1;
      else if(primaryTable[a]->index == -1)return 0;
      else{
        while(1){
          if(overflowTable[a]->value == x){
            return 1;
            break;
          }
          else if(overflowTable[a]->index == -1){
            return 0;
            break;
          }
          else{
            a = overflowTable[a]->index;
          }
        }
      }
    }
    void print(){                                               //function to print both the tables
      cout <<"    Primary table       Overflow table    "<<endl;
      for(int i =0;i<7;i++){
      cout<<"      "<<primaryTable[i]->value<<"                     "<<overflowTable[i]->value<<"      "<<endl;
      }
    }

    void del(int x){                                            //function to delete a value from a node

        int a = hashFunction(x);
        if(primaryTable[a]->value == x){

            if(primaryTable[a]->index == -1){
                primaryTable[a]->value == -1;
                primaryTable[a]->presentStatus = 0;
            }
            else if(overflowTable[a]->index == -1){
                primaryTable[a]->value = overflowTable[a]->value;
                primaryTable[a]->index = -1;
                overflowTable[a]->value = -1;
                overflowTable[a]->presentStatus = 0;
            }
            else{
              primaryTable[a]->value = overflowTable[a]->value;
              while(overflowTable[overflowTable[a]->index]->index != -1){
                overflowTable[a]->value = overflowTable[overflowTable[a]->index]->value;
                a = overflowTable[a]->index;
              }
              overflowTable[a]->value = overflowTable[overflowTable[a]->index]->value;
              overflowTable[overflowTable[a]->index]->value = -1;
              overflowTable[overflowTable[a]->index]->presentStatus = 0;
              overflowTable[a]->index = -1;
            }

        }
        else if(primaryTable[a]->index == -1)cout << "element is not present" << endl;
        else{
          while(1){
            if(overflowTable[a]->value == x){
                if(overflowTable[a]->index == -1){
                  overflowTable[a]->value = -1;
                  overflowTable[a]->presentStatus = 0;
                }else{
                while(overflowTable[overflowTable[a]->index]->index != -1){
                  overflowTable[a]->value = overflowTable[overflowTable[a]->index]->value;
                  a = overflowTable[a]->index;
                }
                overflowTable[a]->value = overflowTable[overflowTable[a]->index]->value;
                overflowTable[overflowTable[a]->index]->value = -1;
                overflowTable[overflowTable[a]->index]->presentStatus = 0;
                overflowTable[a]->index = -1;
              }
              break;
            }
            else if(overflowTable[a]->index == -1){
              cout << "element is not present1" << endl;
              break;
            }
            else{
              a = overflowTable[a]->index;
            }
          }
        }
    }
};

int main(){
  hashOverflow hOver;
  int n,x;
  while(1){
    cout<<"1.insert\n2.print\n3.search\n4.delete"<<endl;
    cin >> n;
    switch (n) {
      case 1:
        cout << "Please enter the number to be entered"<<endl;
        cin >> x;
        hOver.insert(x);
        break;

      case 2:
        hOver.print();
        break;

      case 3:
      cout << "Please enter the number to be searched"<<endl;
      cin >> x;
      hOver.search(x);
      break;

      case 4:
      cout << "Please enter the number to be deleted"<<endl;
      cin >> x;
      hOver.del(x);
      break;

      default:
      return 0;

    }
  }
}
