#include <stdio.h>


int main() {

  int tab[] = {1, 4, 5, 6, 7, 9};
  int a = 5;
  int n = 6;

  while(n > 0) {

    n--;

    if (a == tab[n]) {

      printf("tab contains %d\n", a);
      return 0;

    } 


  }

    printf("tab does not contain %d\n", a);
  return 0;
}
