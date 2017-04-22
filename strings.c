/***
* This program processes one or more strings provided as
* command-line arguments and generates other strings
* based on these arguments using certain pattern.
*
* Examples:
*
*      INPUT:    adez
*      OUTPUT:   a-dD-eEE-zZZZ
*
*      INPUT:    help me please
*      OUTPUT:   h-eE-lLL-pPPP m-eE p-lL-eEE-aAAA-sSSSS-eEEEEE
*
***/

#include <stdio.h>
#include <string.h>

void processString(char* string);

int main(int argc, char* argv[]) {
  if(argc < 2) {
    printf("Usage: please provide string to process.\n");
    return 1;
  }
  for(int i = 1; i < argc; i++) {
    processString(argv[i]);
    printf(" ");
  }
  printf("\n");
  return 0;
}

void processString(char* string) {
  for(int j = 0; j < strlen(string); j++) {
   for(int k = 0; k < j + 1; k++) {
      if(k == 0) {
        printf("%c", string[j]);
      }
      else {
        printf("%c", string[j] - 32);   //ASCII lowercase-uppercase difference is 32
      }
    } 
    if(j < strlen(string) - 1) {
      printf("-");
    }
  }
};
