/*
* This program takes string of characters as an input and generates
* Huffman-encoded stream of 0s and 1s based on it. 
* When counting frequencies of particular characters, whole input
* string is taken into account.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

/*
* Structure:    node
*
* Description:  This structure is used as a node in Huffman tree. Moreover, all nodes
*               are connected with each other using linked list.
* 
* Fields:       character - in case of leaf nodes this field contains character;
*                           otherwise it contains '\0'
*               frequency - contains frequency of character(s) under/in this node
*               code      - in case of leaf nodes this field contains Huffman code;
*                           otherwise it contains NULL pointer
*               next_p    - pointer to next element in nodes' list
*               left      - left child in Huffman tree
*               right     - right child in Huffman tree
*               treeized  - when whole tree is generated, contains 0 for root and 1
*                           for other nodes
*/
typedef struct node {
  char character;
  int frequency;
  char* code;
  struct node* next_p;
  struct node* left;
  struct node* right;
  int treeized;
} node;

/* Function:    calculateFrequencies 
*
* Description:  Takes a string of characters and creates linked list
*               of 'node'-type structures based on this input.
*               This function fills only certain fields of nodes with meaningful data:
*               character, frequency and next_p pointing to next node. 
*
* Parameters:   [in] input - input string
*               [out] start - head of nodes list
*
* Return:       void
*/
void calculateFrequencies(char* input, node** start);

/* Function:    generateTree 
*
* Description:  Takes 'node' list as input and generates Huffman tree based on
*               frequencies of characters. This function extends original list with
*               non-character nodes and adds tree-specific relations between nodes
*               using 'left' and 'right' members of 'node' structure.
*               Root node is the node which has 'treeized' member equal to zero.
*               Other nodes, as well as leaves (=characters) have 'treeized' member
*               equal to 1. 
*               
*
* Parameters:   [in] start - head of nodes list
*               [in] freqSum - length of input, which shall be equal to
*               sum of all frequencies
*
* Return:       void
*/
void generateTree(node** start, const int freqSum);

/* Function:    treeizeNodes 
*
* Description:  Constructs new node based on other nodes which are not already treeized
*               and have lowest frequencies amongst other non-treeized nodes. Links this
*               newly created node with its left and right nodes, creating fragment of future tree.
*
* Parameters:   [in] start - head of nodes list
*               [in/out] newNode - pointer to new empty node
*               [in] right - pointer to right child of newNode
*               [in] left - pointer to left child of newNode
*
* Return:       void
*/
void treeizeNodes(node** start, node** newNode, node **right, node **left);

/* Function:    findLowest 
*
* Description:  Finds node which has lowest frequency amongst all not-yet-treeized nodes.
*
* Parameters:   [in] start - head of nodes list
*               [in/out] lowest - pointer to lowest node
*
* Return:       void
*/
void findLowest(node** start, node** lowest);

/* Function:    calculateCodes 
*
* Description:  Recursive function, which traverses whole Huffman tree
*               and constructs Huffman codes for each of character. When it goes left
*               down the tree, it adds '0' to the code. Otherwise it adds '1'.
*               Then, it triggers itself twice.
*
* Parameters:   [in] nd - current node on which function jumps when traversing down the 
*               Huffman tree
*               [in] code - Fragment of Huffman code already constructed
*
* Return:       void
*/
void calculateCodes(node** nd, char** code);

/* Function:    findRoot 
*
* Description:  Traverses throught list of nodes, finding the one which acts
*               as a root of Huffman tree.
*
* Parameters:   [in] start - head of nodes list
*               [in/out] root - root node of Huffman tree
*
* Return:       void
*/
void findRoot(node** start, node** root);

/* Function:    freeList 
*
* Description:  Frees memory previously allocated for all nodes of Huffman tree
*               and all strings representing Huffman codes.
*
* Parameters:   [in] start - head of nodes list
*
* Return:       void
*/
void freeList(node** start);

/* Function:    encodeInput 
*
* Description:  This function encodes given string using previously
*               generated Huffman codes
*
* Parameters:   [in] input - string to be encoded using Huffman codes
*               [in] start - head of nodes list
*
* Return:       void
*/
void encodeInput(char* input, node** start);

int main (int argc, char* argv[]) {

  node* start = NULL;
  char* input = "In computer science and information theory, a Huffman code is a particular type of optimal prefix code that is commonly used for lossless data compression. The process of finding and/or using such a code proceeds by means of Huffman coding, an algorithm developed by David A. Huffman while he was a Sc.D. student at MIT.";

  const int freqSum = strlen(input);
  calculateFrequencies(input, &start);
  generateTree(&start, freqSum);
  node* root = NULL;
  findRoot(&start, &root);
  printf("PLAIN STRING:\n");
  printf("\n%s\n", input);
  printf("\nASCII\tChar\tCount\tCode\n");
  char* code0 = malloc(2 * sizeof(char));
  strcpy(code0, "0");
  calculateCodes(&(root->left), &code0);
  char* code1 = malloc(2 * sizeof(char));
  strcpy(code1, "1");
  calculateCodes(&(root->right), &code1);
  encodeInput(input, &start); 
  return 0;
}

void encodeInput(char* input, node** start) {
  int codedBitLen = 0;
  int uncodedBitLen = strlen(input) * 8;
  char* input_p = input;
  printf("\nENCODED STRING:\n\n");
  while (*input_p != '\0') {
    node* temp_p = *start;
    while (temp_p != NULL) {
      if (*input_p == temp_p->character) {
        codedBitLen += strlen(temp_p->code);
        printf("%s", temp_p->code);
      }
      temp_p = temp_p->next_p;
    }
    input_p++;
  }
  printf("\n\n");
  printf("Bit length before coding: %d\n", uncodedBitLen);
  printf("Bit length after coding: %d\n", codedBitLen);
  float uncodedBitLenFloat = strlen(input) * 8.0;
  float compressionRate = (codedBitLen/uncodedBitLenFloat) * 100;
  printf("After coding string uses %0.2f percent of original space.\n", compressionRate);
}

void freeList(node** start) {
  node* curr_p = *start;
  node* next_p = (*start)->next_p;
  while (next_p != NULL) {
    if (curr_p->code != NULL) {
      free(curr_p->code);
    }
    free(curr_p);
    curr_p = next_p;
    next_p = next_p->next_p;
  }
  free(curr_p);
}

void findRoot(node** start, node** root) {
  node* temp_p = *start;
  while (temp_p != NULL) {
    if (temp_p->treeized == 0) {
      *root = temp_p;
      return;
    }
    temp_p = temp_p->next_p;
  }
}


void calculateCodes(node** nd, char** code) {
  if ((*nd)->character != '\0') {
    (*nd)->code = *code;
    printf("%d\t%c\t%d\t%s\n", (*nd)->character, (*nd)->character, (*nd)->frequency, *code);
  }
  else {
    int len = strlen(*code) + 2;
    char* newCode0 = malloc(len * sizeof(char));
    strcpy(newCode0, *code);
    strcat(newCode0, "0");
    calculateCodes(&((**nd).left), &newCode0);
    char* newCode1 = malloc(len * sizeof(char));
    strcpy(newCode1, *code);
    strcat(newCode1, "1");
    calculateCodes(&((**nd).right), &newCode1);
    free(*code);
  }
}

void generateTree(node** start, const int freqSum) {
  while (1) {
    node* right = NULL;
    findLowest(start, &right);
    node* left = NULL;
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
  (*newNode)->code = NULL;
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
  (*lowest)->treeized = 1;
}

void calculateFrequencies(char* input, node** start) {
  char* char_p = input;

  // special treatment for first character due to efficiency,
  // as list is not pointing to a valid node yet
  *start = malloc(sizeof(node));
  (*start)->character = *char_p;
  (*start)->frequency = 1;
  (*start)->next_p = NULL;
  (*start)->right = NULL;
  (*start)->left = NULL;
  (*start)->treeized = 0;
  (*start)->code = NULL;
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
        newNode->code = NULL;
        list_p->next_p = newNode;
        break;
      }
    list_p = list_p->next_p;
    }
  char_p++;
  }
}
