#include<iostream>
#include<string>
using namespace std;

struct student{
  string roll_no;
  string name;
  int age;
  string gender;
};

int main{
  struct student batch[40];
  int n;
  while(n > 40 || n == 0){
    cout << "Enter the batch strength(not more than 40)" << endl;
    cin >> n;
  }
  for(int j = 0; j < n; j++){
    string roll,name,gender;
    int age;
    cin >> roll >> name >> age >> gender;
    batch[i] = {roll,name,age,gender};
    //cin >> batch[i].roll_no >> batch[i].name >> batch[i].age >> batch[i].gender;
  }
  for(int k = 0; k < n; k++){
    cout << batch[i].roll_no << " " << batch[i].name << " " << batch[i].age << " " << batch[i].gender;
  }
  cout << endl;
  return 0;
}
