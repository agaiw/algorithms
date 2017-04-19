#include <stdio.h>



int main() {

  int tab[] = {10, 2, 3, 4, 70, 33, 33, 2, 2, 2, 2, 10, 1};

  int n = 13;
  int i = 0;
  int c = 0;

  int sort[101];

  for (int i = 0; i < 101; i++) {
    sort[i] = 0;
  }

  while (n >= 0) {
    n--; 
    sort[tab[n]]++;
  }

  for (int i = 0; i < 101; i++) {
    if (sort[i] > c) {
      c = i;
    }
  }

  printf("Most frequent value is: %d\n", c);

  return 0;

}
