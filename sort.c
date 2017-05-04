#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 20

/**
* This program contains implementation of the following
* sort algorithms: bubble sort, insertion sort and shell sort.
* Array of random integers is generated and copied into
* other arrays, separate for each of algorithms.
* Input array is also presented to the user.
* Sorting functions are triggered. Results of sorting
* are printed out to the user.
**/

void bubbleSort(int array[], int size);

void insertionSort(int array[], int size);

void shellSort(int array[], int size);

void printArray(int array[], int size);

time_t t;    // needed to initialize random number generator

int main (int argc, char* argv[]) {

  srand((unsigned)time(&t));  // computing seed for random numbers generator

  int arr[ARRAY_SIZE];

  int arrBubble[ARRAY_SIZE];
  int arrInsertion[ARRAY_SIZE];
  int arrShell[ARRAY_SIZE];

  for (int i = 0; i < ARRAY_SIZE; ++i) {
    arr[i] = rand() % 100;
    arrBubble[i] = arr[i];    // random numbers are copied so separate
                              // arrays are used in each of algorithms
    arrInsertion[i] = arr[i];
    arrShell[i] = arr[i];
  }

  // Printing original data
  printf("Random data for bubble sorting:\n");
  printArray(arrBubble, ARRAY_SIZE);
  printf("\nRandom data for insertion sorting:\n");
  printArray(arrInsertion, ARRAY_SIZE);
  printf("\nRandom data for shell sorting:\n");
  printArray(arrShell, ARRAY_SIZE);

  // Sorting data
  bubbleSort(arrBubble, ARRAY_SIZE);
  insertionSort(arrInsertion, ARRAY_SIZE);
  shellSort(arrShell, ARRAY_SIZE);

  // Printing sorted data
  printf("\nData after bubble sorting:\n");
  printArray(arrBubble, ARRAY_SIZE);
  printf("\nData after insertion sorting:\n");
  printArray(arrInsertion, ARRAY_SIZE);
  printf("\nData after shell sorting:\n");
  printArray(arrShell, ARRAY_SIZE);
}

void bubbleSort(int array[], int size) {
  int temp;
  int iter = size;
  for (int i = 0; i < iter; ++i) {
    for (int j = 0; j < (size - 1); ++j) {
      if(array[j] > array[j + 1]) {    // if numbers are in wrong order,
        temp = array[j + 1];           // swap them using temporary variable
        array[j + 1] = array[j];
        array[j] = temp;
      }
    }
    --size;
  }
}

void insertionSort(int array[], int size) {
  for (int i = 1; i < size; ++i) {
    for (int j = i; j > 0; --j) {
      if (array[j] < array[j-1]) {
        int temp = array[j];
        array[j] = array[j-1];
        array[j-1] = temp;
      }
    }
  }
}

void shellSort(int array[], int size) {
  int interval = size;
  while (interval > 1) {
    interval = interval / 2;  // first used interval is around half of array size
    for (int i = 0; i < (size - interval); ++i) {
      if (array[i] > array[i+interval]) {
        int temp = array[i];
        array[i] = array[i+interval];
        array[i+interval] = temp;
      }
    }
  };
  insertionSort(array, ARRAY_SIZE);   // last pass of shellSort is always
                                      // an ordinary insertion sort
                                      // so previously written function can be reused
}





void printArray(int array[], int size) {

  for (int i = 0; i < size; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");
}
