#include <stdio.h>
#include <string.h>


typedef struct listNode {
  char character;
  int frequency;
  *listNode next_p;
} listNode;


int main (int argc, char* argv[]) {
  listNode* list = NULL;
  char* input = "Odra to rzeka modra";
  calculateFrequencies(input, &list);

}

void calculateFrequencies(char* input, listNode** list) {
  char* char_p = input;

  // special treatment for first character due to efficiency,
  // as list is not pointing to a valid node yet
  // TODO add handling for empty/null input
  list = malloc(sizeof(listNode));
  list->character = *char_p;
  list->frequency = 1;
  list->next_p = NULL;

  // handling for rest of characters
  while(*char_p != '\0') {
    listNode* list_p = list;
    while (1) {
      if (list_p->character == *char_p) {
        list_p->frequency++;
        break;
      }
      if (list_p->next_p == NULL) {
        listNode* newNode = malloc(sizeof(listNode));
        newNode->character = *char_p;
        newNode->frequency = 1;
        newNode->next_p = NULL;
        list_p->next_p = newNode;
        break;
      }
    }
  }
}
