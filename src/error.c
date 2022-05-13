#ifndef _ERROR_
#define _ERROR_
#include <assert.h>
#include <stdio.h>
#include "defs.h"

struct grammer_error{
  int errorkind;
  const char* str;
  //void (*handler) (int errorkind);
} errors[] = {
  {ERROR_x00, "declaration missing ;"},
  {ERROR_x01, "declaration syntax error"},
  {ERROR_x02, "division by zero"},
  {ERROR_x03, "expression syntax error"},
  {ERROR_x04, "variable undeclaration"},
  {ERROR_x05, "while statement must have od"},
  {ERROR_x06, "while statement must have do"},
  {ERROR_x07, "if statement must have fi"},
  {ERROR_x08, "missing left parenthesis"},
  {ERROR_x09, "missing right parenthesis"},
  {ERROR_x10, "declaration missing ','"},
  {ERROR_x11, "unknown mistake"},
};


/**
 * @brief 
 * printf specific error infomation
 * @param erroinfo 
 */
void Log(int errorkind) {
  printf("%s\n", errors[errorkind].str);
}

void Assert(char* errinfo) {
  assert(errinfo);
}

// more TODO

#endif