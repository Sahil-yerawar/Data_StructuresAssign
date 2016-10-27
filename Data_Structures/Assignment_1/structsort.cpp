/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 1
  Problem 3:- Using an array structures to deifne a class of students and sort it according to their roll numbers
  */
#include<iostream>
#include<string>

using namespace std;

struct student{                                 //defining student structure
  string roll_no;
  string name;
  int age;
  string gender;
};
void insertSort(struct student a[40],int size){   // Modified InsertionSort for struct student
  for(int j = 0; j < size; j++){
  for(int i = 0; i < size-1; i++){
    if((a[i+1].roll_no).compare(a[i].roll_no) < 0){   //to compare their roll numbers, we use compare() function.
      int j = i+1;
      struct student val = a[j];
      while(j >  0 && (a[j].roll_no).compare(a[j-1].roll_no) < 0){
	        a[j] = a[j-1];
	        j--;
      }
      a[j] = val;
    }
  }
  }

}

int main(){
  struct student batch[40];                             // A class of students with maximum class size 40
  int n;
  while(n > 40 || n == 0){
    cout << "Enter the batch strength(not more than 40)" << endl;
    cin >> n;
  }
  for(int i = 0; i < n; i++){                           //Entering the details of each student
    cout << "Enter roll no, then name, then age, then gender " << endl;
    cin >> batch[i].roll_no >> batch[i].name >> batch[i].age >> batch[i].gender;
  }
  insertSort(batch,n);                                  //Sorting the students according to their roll number
  cout << "The Sorted order of students is:- "<< endl;
  for(int i = 0; i < n; i++){                           // Displaying the sorted order

    cout << batch[i].roll_no << " " << batch[i].name << " " << batch[i].age << " " << batch[i].gender << endl;
  }
  cout << endl;
  return 0;
}
