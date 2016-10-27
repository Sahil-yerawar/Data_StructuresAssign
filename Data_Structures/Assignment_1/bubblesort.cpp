/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 1
  Problem 4:- Implementing BubbleSort
  */
#include<iostream>
#include<cstdio>

using namespace std;

void bubbleSort(int array[200], int size){              // Function defining bubblesort operation.
  for(int i = 0; i < size; i++){
    for(int j = 1; j < size; j++){
      if(array[j] < array[j-1]){                        //whenever the element is lesser than the element behind it
      int temp = array[j];                              //swapping with the two elements take place
      array[j] = array[j-1];
      array[j-1] = temp;}
    }
  }
  for(int k = 0; k < size; k++){                        // Printing of the final sorted array
    cout << array[k] << " " ;
  }
  cout << endl;
}

int main(){
  int n = 0,set[200] = {0};                             // Declaring an array o size 200(size can be less than that)
  while(n > 200 || n == 0){
    cout << "Enter the size of input(less than 200)" << endl;
    cin >> n;
  }
  for(int i = 0; i < n; i++){
    cout << "Enter " << i+1 << "th element" << endl;
    cin >> set[i];                                      // Entering the array elements
  }
  bubbleSort(set,n);
  return 0;
}
