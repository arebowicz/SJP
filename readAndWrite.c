#include "readAndWrite.h"

int polishWcharToInt(wchar_t wc) {
  if (wc == L'a')
    return wc-L'a';
  else if (wc == L'ą')
    return 1;
  else if (wc >= L'b' && wc <= L'c')
    return wc-L'a'+1;
  else if (wc == L'ć')
    return 4;
  else if (wc >= L'd' && wc <= L'e')
    return wc-L'a'+2;
  else if (wc == L'ę')
    return 7;
  else if (wc >= L'f' && wc <= L'l')
    return wc-L'a'+3;
  else if (wc == L'ł')
    return 15;
  else if (wc >= L'm' && wc <= L'n')
    return wc-L'a'+4;
  else if (wc == L'ń')
    return 18;
  else if (wc == L'o')
    return wc-L'a'+5;
  else if (wc == L'ó')
    return 20;
  else if (wc >= L'p' && wc <= L's')
    return wc-L'a'+6;
  else if (wc == L'ś')
    return 25;
  else if (wc >= L't' && wc <= L'z')
    return wc-L'a'+7;
  else if (wc == L'ź')
    return 33;
  else if (wc == L'ż')
    return 34;
  else
    return -1;
}

wchar_t intToPolishWchar(int i) {
  if (i == 0)
    return L'a'+i-0;
  else if (i == 1)
    return L'ą';
  else if (i >= 2 && i <= 3)
    return L'a'+i-1;
  else if (i == 4)
    return L'ć';
  else if (i >= 5 && i <= 6)
    return L'a'+i-2;
  else if (i == 7)
    return L'ę';
  else if (i >= 8 && i <= 14)
    return L'a'+i-3;
  else if (i == 15)
    return L'ł';
  else if (i >= 16 && i <= 17)
    return L'a'+i-4;
  else if (i == 18)
    return L'ń';
  else if (i == 19)
    return L'a'+i-5;
  else if (i == 20)
    return L'ó';
  else if (i >= 21 && i <= 24)
    return L'a'+i-6;
  else if (i == 25)
    return L'ś';
  else if (i >= 26 && i <= 32)
    return L'a'+i-7;
  else if (i == 33)
    return L'ź';
  else if (i == 34)
    return L'ż';
  else
    return L'0';
}

/*
  number of words stored in dictionary
*/
int WORD_IN_DICT_NUM;

void readDict(FILE *dict) {
  if(ROOT == NULL)
    ;
  else {
    wint_t wc;
    int m = 0;
    wchar_t word[MAX_WORD_LEN];
    word[0] = L'\0';
    while((wc = fgetwc(dict)) != WEOF) {
      if(wc == L'\n') {
        word[m] = L'\0';
        if(m>0) {
          addWord(word, ROOT->children[polishWcharToInt(*word)]);
          m = 0;
          ++WORD_IN_DICT_NUM;
        }
       } else
        word[m++] = wc;
    }
  }
}

void write01(tNode *node, FILE *file01) {
  if(node == NULL)
    return;
  else {
    if(node->isWord == true)
      fputwc(L'1', file01);
    else
      fputwc(L'0', file01);
    int i;
    for(i=0; i < NUM_OF_LETTERS; ++i)
      if(node->children[i] == NULL)
        fputwc(L'0', file01);
      else
        fputwc(L'1', file01);
    for(i=0; i < NUM_OF_LETTERS; ++i)
      write01(node->children[i], file01);
  }
}

/*
  to finish the recursive dictionary reading process (from file: 01.TXT)
  if TRUE - the last word has been correctly read
*/
static bool EOF01 = false;

/*
  it is necessary to get one more character from stream
  to know if it is end of stream (file 01.TXT)
*/
static wint_t BUF[2] = {L'0', L'0'};
static int ACT_BUF = 0;

static wint_t fgetwcbuf(FILE *file) {
  return (ACT_BUF > 0) ? BUF[--ACT_BUF] : fgetwc(file);
}

static void fungetwcbuf(wint_t wc) {
  BUF[ACT_BUF++] = wc;
  return;
}

void read01(tNode *node, FILE *file01) {
  if(node == NULL || EOF01 == true)
    return;
  else {
    wchar_t node01[NUM_OF_LETTERS+1];
    wint_t wc;
    int i = 0;
    while((wc=fgetwcbuf(file01)) != WEOF && i <= NUM_OF_LETTERS)
      node01[i++] = wc;
    fungetwcbuf(wc);
    node->isWord = ((node01[0] == L'0') ? false : true);
    if(node->isWord == true)
      ++WORD_IN_DICT_NUM;
    if(BUF[0] == WEOF) {
      EOF01 = true;
      return;
    }
    for(i=1; i<=NUM_OF_LETTERS; ++i) {
      if(node01[i] == L'0')
        node->children[i-1] = NULL;
      else {
        node->children[i-1] = mallocTreeNode();
        read01(node->children[i-1], file01);
      }
    }
  }
}

/*
  to store a single word
*/
wchar_t WORD[MAX_WORD_LEN];

static void writeWord(int len, FILE *fileDict) {
  int i = 0;
  while(i<len)
    fputwc(WORD[i++], fileDict);
  fputwc(L'\n', fileDict);
}

void writeDict(tNode *node, int lvl, wchar_t wc, FILE *fileDict) {
  if(node == NULL)
    return;
  else {
    WORD[lvl] = wc;
    if(node->isWord == true) {
      WORD[lvl+1] = L'\0';
      writeWord(lvl+1, fileDict);
    }
    int i;
    for(i=0; i<NUM_OF_LETTERS; ++i)
      writeDict(node->children[i], lvl+1, intToPolishWchar(i), fileDict);
  }
}

bool readWord() {
  wint_t wc;
  int i = 0;
  while(i<MAX_WORD_LEN) {
    wc = getwchar();
    if(wc != WEOF && wc != L'\n') {
      if(polishWcharToInt(wc) == -1)
        return false;
      WORD[i++] = wc;
    } else if(i == 0 && (wc == L'\n' || wc == WEOF))
      return false;
    else {
      WORD[i] = L'\0';
      return true;
    }
  }
  return false;
}