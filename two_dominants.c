#include <stdio.h>
#define LIMIT 100

int main() {

  int testArray[] = {1, 4, 23, 98, 77, 60, 60, 34, 42, 86, 22, 21, 10, 94, 55, 55, 55, 60};
  int n = 18;               // size of testArray
  int max = 0;              // how many times dominant number(s) ocurr
  int sort[LIMIT];      // cardinality array

  for(int i = 0; i < LIMIT; i++) {

    sort[i] = 0;            // uninitialized table contains garbage

  }

  for(int i = 0; i < n; i++) {

    sort[testArray[i]]++;

  }

  for(int j = 0; j < LIMIT; j++) {

    if(max < sort[j]) {

      max = sort[j];

    }
  }

  for(int k = 0; k < LIMIT; k++) {

    if(sort[k] == max) {

      printf("Number %d is one of most frequent numbers.\n", k);

    }
  }
  printf("Each of mentioned numbers ocurred %d times.\n", max);
  return 0;
}
