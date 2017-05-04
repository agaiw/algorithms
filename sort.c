#include <stdio.h>
#define ARRAY_SIZE 15

void bubblesort(int array[], int size);

void shellsort(int array[], int size);

void insertsort(int array[], int size);

int main (int argc, char* argv[]) {

  int array[] = {5, 65, 51, 6, 16, 12, 13, 29, 0, 81, 1, 2, 3, 43, 8};

  // Printing unsorted data
  for (int i = 0; i < ARRAY_SIZE, ++i) {
    printf("%d "array[i]);
  }
  printf("\n");

  // Sorting data
  bubblesort(array, 15);
  //shellsort();
  //insertsort();

}

void bubblesort(int array[], int size) {

  int temp;
  int iter = size;
  for (int i = 0; i < iter; ++i) {
    for (int j = 0; j < size; ++j) {
      if(array[j] > array[j + 1]) {
        temp = array[j + 1];
        array[j + 1] = array[j];
        array[j] = temp;
      }
    }
    --size;
  }
  for (int i = 0; i < 15; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");
}


void shellsort(int array[], int size) {

}
