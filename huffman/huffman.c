#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
  char character;
  int frequency;
  struct node* next_p;
  struct node* left;
  struct node* right;
  int treeized;
} node;

void calculateFrequencies(char* input, node** start);
void generateTree(node** start, const int freqSum);
int sthToTreeize(node** start);
void treeizeNodes(node** start, node** newNode, node **right, node **left);
void findLowest(node** start, node** lowest);
void calculateCodes(node** start, char* code);
void findRoot(node** start, node** root);

int main (int argc, char* argv[]) {
  node* start = NULL;
  char* input = "odra modra";
  const int freqSum = strlen(input);
  calculateFrequencies(input, &start);
  generateTree(&start, freqSum);
  node* root = NULL;
  findRoot(&start, &root);

  char* code = malloc(sizeof(char));
  strcpy(code, "0");
  calculateCodes(&root->left, code);
  strcpy(code, "1");
  calculateCodes(&root->right, code);
 
  // test
  node* temp_p = start;
  while (temp_p != NULL) {
    printf("ch: %c, fr: %d, addr: %p, next: %p, r: %p, l: %p, tree: %d\n", 
           temp_p->character,
           temp_p->frequency, temp_p, temp_p->next_p, temp_p->right,
           temp_p->left, temp_p->treeized);
    temp_p = temp_p->next_p;
  }
  return 0;
}

void findRoot(node** start, node** root) {
  node* temp_p = *start;
  while (temp_p != NULL) {
    if (temp_p->treeized == 0) {
      *root = temp_p;
      return;
    }
  }
}


void calculateCodes(node** nd, char* code) {
  if ((*nd)->character != '\0') {
    printf("character: %c, code: %s\n", (*nd)->character, code);
  }
  else {
    int len = strlen(code) + 1;
    char* newCode = malloc(len * sizeof(char));
    strcpy(newCode, code);
    strcat(newCode, "0");
    //calculateCodes((**nd).left, newCode);
    strcpy(newCode, code);
    strcat(newCode, "1");
    //calculateCodes((**nd)->right, newCode);
    free(code);
  }
}

void generateTree(node** start, const int freqSum) {
  while (sthToTreeize(start)) {
    node* right = malloc(sizeof(node));
    findLowest(start, &right);
    node* left = malloc(sizeof(node));
    findLowest(start, &left);
    node* newNode = malloc(sizeof(node));
    treeizeNodes(start, &newNode, &right, &left);
    if (newNode->frequency == freqSum) {
      return;
  }
  }  
}

void treeizeNodes(node** start, node** newNode, node **right, node **left) {
  (*newNode)->right = *right;
  (*newNode)->left = *left;
  (*newNode)->frequency = (*right)->frequency + (*left)->frequency;
  (*newNode)->character = '\0';
  (*newNode)->treeized = 0;
  (*newNode)->next_p = NULL;
  node* temp_p = *start;
  while (temp_p != NULL) {
    if (temp_p->next_p == NULL) {
      temp_p->next_p = *newNode;
      break;
    }
    temp_p = temp_p->next_p;
  }
}

void findLowest(node** start, node** lowest) {
  node* temp_p = *start;
  int low = INT_MAX; 
  while (temp_p != NULL) {
    if (temp_p->treeized == 0 && (temp_p->frequency < low)) {
      *lowest = temp_p;
      low = temp_p->frequency;
    }
    temp_p = temp_p->next_p;
  }
  printf("lowest: %d\n", (*lowest)->frequency);
  (*lowest)->treeized = 1;
}

int sthToTreeize(node** start) {
  int result = 0;
  node* temp_p = *start;
  while (temp_p != NULL) {
    if (temp_p->treeized == 0) {
      result = 1;
    }
    temp_p = temp_p->next_p; 
  }
  return result;
}

void calculateFrequencies(char* input, node** start) {
  char* char_p = input;

  // special treatment for first character due to efficiency,
  // as list is not pointing to a valid node yet
  // TODO add handling for empty/null input
  *start = malloc(sizeof(node));
  (*start)->character = *char_p;
  (*start)->frequency = 1;
  (*start)->next_p = NULL;
  (*start)->right = NULL;
  (*start)->left = NULL;
  (*start)->treeized = 0;
  char_p++;
  // handling for rest of characters
  while(*char_p != '\0') {
    node* list_p = *start;
    while (1) {
      // char is already in the list
      if (list_p->character == *char_p) {
        list_p->frequency++;
        break;
      }
      // end of list reached, character not found
      if (list_p->next_p == NULL) {
        node* newNode = malloc(sizeof(node));
        newNode->character = *char_p;
        newNode->frequency = 1;
        newNode->next_p = NULL;
        newNode->right = NULL;
        newNode->left = NULL;
        newNode->treeized = 0;
        list_p->next_p = newNode;
        break;
      }
    list_p = list_p->next_p;
    }
  char_p++;
  }
}
