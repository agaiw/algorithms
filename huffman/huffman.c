#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct listNode {
  char character;
  int frequency;
  struct listNode* next_p;
} listNode;

void calculateFrequencies(char* input, listNode** list);

int main (int argc, char* argv[]) {
  listNode* list = NULL;
  char* input = "Odra to jest rzeka modra";
  calculateFrequencies(input, &list);
  listNode* temp_p = list;

  while (temp_p != NULL) {
    printf("character: %c, frequency: %d\n", temp_p->character, temp_p->frequency);
    temp_p = temp_p->next_p;
  }
  return 0;
}

void calculateFrequencies(char* input, listNode** list) {
  char* char_p = input;

  // special treatment for first character due to efficiency,
  // as list is not pointing to a valid node yet
  // TODO add handling for empty/null input
  *list = malloc(sizeof(listNode));
  (*list)->character = *char_p;
  (*list)->frequency = 1;
  (*list)->next_p = NULL;
  char_p++;
  // handling for rest of characters
  while(*char_p != '\0') {
    listNode* list_p = *list;
    while (1) {
      // char is already in the list
      if (list_p->character == *char_p) {
        list_p->frequency++;
        break;
      }
      // end of list reached, character not found
      if (list_p->next_p == NULL) {
        listNode* newNode = malloc(sizeof(listNode));
        newNode->character = *char_p;
        newNode->frequency = 1;
        newNode->next_p = NULL;
        list_p->next_p = newNode;
        break;
      }
    list_p = list_p->next_p;
    }
  char_p++;
  }
}
