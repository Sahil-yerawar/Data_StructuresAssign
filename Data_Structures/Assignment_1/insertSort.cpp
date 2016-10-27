/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 1
  Problem 1:- Implementing InsertionSort
  */

#include<iostream>
#include<cstdio>
using namespace std;
/* function definition for insertion sort*/
void insertSort(int a[200],int size){
  for(int j = 0; j < size; j++){
  for(int i = 0; i < size-1; i++){
    if(a[i+1] < a[i]){                  //whenever an element is lesser than the element behind it, it shifts back
      int j = i+1;                      // till it finds an element greater than the considered element , at which it stops.
      int val = a[j];
      while(j >  0 && a[j] < a[j-1]){   // while loop used till we find a greater element
	//int temp = a[j];
	a[j] = a[j-1];
	//a[j-1] = temp;
	j--;
      }
      a[j] = val;                       // When it finds the element, it does final swapping  so that it is placed in order.
    }
  }
  }
  cout << "The sorted array is:- " << endl;
  for(int j = 0; j < size; j++){        // Printing of array within the program
    cout << a[j] << " " ;}
  cout << endl;
}
/* Implementation of insertion sort in the program
   maximum size of the array is 200 and each element is taken from the user*/
int main(){
  int n = 0;
  while(n > 200 || n == 0){

  cout << "Enter the number of inputs (less than 200)" << endl;
  cin >> n;
  }
  //cout << n << endl;
  int set[200] = {0};
  for(int i = 0; i < n; i++){
    cout << "Enter " << i+1 <<"th element" << endl;
    cin >> set[i];
  }
  insertSort(set,n);
  return 0;
  }/*
do{
    cin >> n;
  }while{
    n <= 200;}*/
