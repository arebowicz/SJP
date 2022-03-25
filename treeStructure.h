#ifndef TREESTRUCTURE_H_INCLUDED
#define TREESTRUCTURE_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>

#define NUM_OF_LETTERS 35

typedef struct treeNode {
  bool isWord;
  struct treeNode *children[NUM_OF_LETTERS];
} tNode;

#include "readAndWrite.h"

extern tNode *ROOT;

tNode *mallocTreeNode();
void treeInit();
void deleteTree(tNode *);
int addWord(wchar_t *, tNode *);
bool isInTree(wchar_t *, tNode *);

#endif