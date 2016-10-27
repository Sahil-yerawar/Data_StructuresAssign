/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 1
  Problem 2:- Implementing SelectionSort
  */

#include<iostream>
#include<cstdio>

using namespace std;
/*function definition for selection sort*/
void selectionSort(int array[200], int size){
  for(int i = 0; i < size-1; i++){        // traversing over the array

    int min = i;                          // assigning the traversing element to be minimum
    for(int j = i+1; j < size; j++){      // checking over the remaining array to find smallest element less the assigned
      if(array[j] < array[min]){          // "minimum". Then we swap it with the found minimum so that the element is in
	min = j;                                // place
      }
      // array[i] = min;
    }
  if(min != i){int temp = array[i];
    array[i] = array[min];
    array[min] = temp;}
  }
  cout << "The sorted array is:- " << endl;  // Printing the sorted array
  for(int i = 0; i < size; i++){
    cout << array[i] << " " ;
  }
  cout << endl;
}
/*Implementation of SelectionSort in the program
  maximum array size - 200
  input(from the user) can be any integer*/

int main(){
  int n;
  while(n > 200 || n == 0){
    cout << "Enter the size(less than 200)" << endl;
    cin >> n;
  }

   int set[200] = {0};
   for(int i = 0; i < n;i++){
     cout << "Enter " << i+1 << "th integer" << endl;
     cin >> set[i];
   }
   selectionSort(set,n);
   return 0;
}
