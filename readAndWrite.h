#ifndef READANDWRITE_H_INCLUDED
#define READANDWRITE_H_INCLUDED

#include <stdio.h>
#include <wchar.h>
#include "treeStructure.h"

#define MAX_WORD_LEN 50

extern wchar_t WORD[MAX_WORD_LEN];
extern int WORD_IN_DICT_NUM;

void readDict(FILE *);
int polishWcharToInt(wchar_t);
wchar_t intToPolishWchar(int);
void write01(tNode *, FILE *);
void read01(tNode *, FILE *);
void writeDict(tNode *, int , wchar_t , FILE *);
bool readWord();

#endif