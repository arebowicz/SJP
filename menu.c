#include "menu.h"

#define FILE_DICT "dict-03-20-2022.txt"
#define FILE_01 "01-03-20-2022.txt"

static void printRemember();
static void printMenu();
static void printCommandError();
static void cleanUpInput();
static void readFromDict();
static void readFrom01();
static void writeToDict();
static void writeTo01();
static void searchWord();

void menu() {
  setlocale(LC_ALL, "en_US.UTF-8");
  printRemember();
  printMenu();
  wint_t wc;
  WORD_IN_DICT_NUM = 0;
  while((wc = getwchar()) != WEOF) {
    /*
      getwchar() != L'\n'
        correct command is '1'/'2'/.../'6' + '\n'
        so it is necessary to get one more character
        from input stream
    */
    if(getwchar() != L'\n' || wc < L'1' || wc > L'6') {
      printCommandError();
      cleanUpInput();
      continue;
    }
    switch (wc){
      case L'1':
        readFromDict();
        break;
      case L'2':
        readFrom01();
        break;
      case L'3':
        writeToDict();
        break;
      case L'4':
        writeTo01();
        break;
      case L'5':
        searchWord();
        break;
      case L'6':
        wc = WEOF;
        break;
    }
    if(wc == WEOF)
      break;
    wprintf(L"\n");
    printMenu();
  }
  deleteTree(ROOT);
}

static void printRemember() {
  wprintf(L"---------------------------\n");
  wprintf(L"REMEMBER: READ README FIRST\n");
  wprintf(L"---------------------------\n");
}

static void printMenu() {
  wprintf(L"PROGRAM MENU:\n");
  if(WORD_IN_DICT_NUM != 0)
    wprintf(L"words in dictionary: %d\n", WORD_IN_DICT_NUM);
  if(WORD_IN_DICT_NUM == 0) {
    wprintf(L"1) read dict from dict.txt file\n");
    wprintf(L"2) read dict from 01.txt file\n");
  }
  if(WORD_IN_DICT_NUM != 0) {
    wprintf(L"3) write dict to dict.txt file\n");
    wprintf(L"4) write dict to 01.txt file\n");
    wprintf(L"5) search word in dict\n");
  }
  wprintf(L"6) exit\n");
  wprintf(L"choose an option and then press enter...\n");
  return;
}

static void printCommandError() {
  wprintf(L"invalid command!\n");
  wprintf(L"try again...\n");
  return;
}

/*
  it is necessary to get all the rest characters
  from input when incorrect command
*/
static void cleanUpInput() {
  while(getwchar() != L'\n')
    ;
  return;
}

static void printWaitAsec() {
  wprintf(L"wait a sec...\n");
  return;
}

static void printDone() {
  wprintf(L"done!\n");
  return;
}

static void readFromDict() {
  if(ROOT == NULL) {
    FILE *dict = NULL;
    dict = fopen(FILE_DICT, "r");
    if(dict != NULL) {
      printWaitAsec();
      treeInit();
      readDict(dict);
      printDone();
    }
    fclose(dict);
  }
}

static void readFrom01() {
  if(ROOT == NULL) {
    FILE *file01;
    file01 = fopen(FILE_01, "r");
    if(file01 != NULL) {
      printWaitAsec();
      ROOT = mallocTreeNode();
      read01(ROOT, file01);
      printDone();
    }
    fclose(file01);
  }
}

static void writeTo01() {
  if(ROOT != NULL) {
    FILE *file01;
    file01 = fopen(FILE_01, "w");
    if(file01 != NULL) {
      printWaitAsec();
      write01(ROOT, file01);
      printDone();
    }
    fclose(file01);
  }
}

static void writeToDict() {
  if(ROOT != NULL) {
    FILE *fileDict;
    fileDict = fopen(FILE_DICT, "w");
    if(fileDict != NULL) {
      printWaitAsec();
      int i;
      WORD[0] = L'0';
      for(i=0; i<NUM_OF_LETTERS; ++i)
        writeDict(ROOT->children[i], 0, intToPolishWchar(i), fileDict);
      printDone();
    }
    fclose(fileDict);
  }
}

static void searchWord() {
  if(ROOT != NULL) {
    if(readWord() == true) {
      if(isInTree(WORD, ROOT->children[polishWcharToInt(WORD[0])]))
        wprintf(L"successfully found in dictionary!\n");
      else
        wprintf(L"not found in dictionary :(\n");
    } else {
      cleanUpInput(); /* but what about an empty line? -- check README */
      wprintf(L"hey! it isn't a word...\n");
    }
  }
}