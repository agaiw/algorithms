
/***
* DESCRIPTION
* This program finds most frequent value or values
* in a randomly initialized array of integers
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100000          // size of testArray
#define LIMIT 10000          // maximum value for elements of testArray

/***
* GLOBALS
**/

int testArray[SIZE];         // test array
int max = 0;                 // how many times dominant number(s) ocurr
int cardArray[SIZE][2];      // array of cardinalities
time_t t;                    // needed to initialize random number generator

/***
* FUNCTION DECLARATIONS
**/

int compare_ints(const void* a, const void* b);
void insert_card(int number, int card);

int main() {
  srand((unsigned)time(&t));

  for(int i = 0; i < SIZE; i++) {
    testArray[i] = rand() % LIMIT;  // testArray init with random values
    cardArray[i][0] = -1;           // cardArray init; -1 means empty slot
    cardArray[i][1] = 0;
  }

  qsort(testArray, SIZE, sizeof(int), compare_ints);

  int currentCard = 1;

  for(int j = 0; j < (SIZE - 1); j++) {
    if(testArray[j] == testArray[j+1]) {   // stepping through same values in sorted array
      currentCard++;
    }   
    else {                                 // different value encountered
      if(max < currentCard) {
        max = currentCard;
      }
      insert_card(testArray[j], currentCard);
      currentCard = 1;
    }
  }

  for(int l = 0; l < SIZE; l++) {
    if(cardArray[l][1] == max) {
      printf("Number %d is one of the most frequent numbers.\n", cardArray[l][0]);
    }
  }
  printf("Each of mentioned numbers ocurred %d times.\n", max);
  return 0;
}

int compare_ints(const void* a, const void* b) {
  int _a = *(int*)a;
  int _b = *(int*)b;
  if (_a < _b) {
    return -1;
  }
  else if (_a == _b) {
    return 0;
  }
  else {
    return 1;
  }
}

void insert_card(int number, int card) {
  for(int k = 0; k < SIZE; k++) {
    if(cardArray[k][0] == -1) {       // empty slot found
      cardArray[k][0] = number;
      cardArray[k][1] = card;
      return;
    }
  }  
}
