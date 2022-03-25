#include "treeStructure.h"

tNode *ROOT = NULL;

tNode *mallocTreeNode() {
  tNode *tmp = (tNode *) malloc(sizeof(tNode));
  if (tmp != NULL) {
    tmp->isWord = false;
    int i;
    for(i=0; i < NUM_OF_LETTERS; ++i)
      tmp->children[i] = NULL;
  }
  return tmp;
}

void treeInit() {
  ROOT = mallocTreeNode();
  if (ROOT != NULL) {
    int i;
    for(i=0; i < NUM_OF_LETTERS; ++i)
      ROOT->children[i] = mallocTreeNode();
  }
}

void deleteTree(tNode *node) {
  if(node == NULL)
    return;
  else {
    int i;
    for(i=0; i<NUM_OF_LETTERS; ++i)
      deleteTree(node->children[i]);
    free(node);
  }
}

int addWord(wchar_t *word, tNode *node) {
  if(*(word+1) == L'\0')
    if(node->isWord == true)
      return 2;
    else {
      node->isWord = true;
      return 1;
    }
  else {
    int i = polishWcharToInt(*++word);
    if(node->children[i] == NULL) {
      node->children[i] = mallocTreeNode();
      if(node->children[i] == NULL)
        return 0;
    }
    return addWord(word, node->children[i]);
  }
}

bool isInTree(wchar_t *word, tNode *node) {
  if(node == NULL)
    return false;
  else if(*(word+1) == L'\0') {
    if(node->isWord == true)
      return true;
    else
      return false;
  } else {
    int i = polishWcharToInt(*++word);
    return isInTree(word, node->children[i]);
  }
}