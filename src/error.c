#ifndef _ERROR_
#define _ERROR_
#include <assert.h>
#include <stdio.h>
#include "defs.h"
#include "color.h"

struct grammer_error{
  int errorkind;
  const char* str;
  // void (*handler) (int errorkind,int row, int col);
} errors[] = {
  {ERROR_x00, "missing ;"},
  {ERROR_x01, "declaration syntax error"},
  {ERROR_x02, "division by zero"},
  {ERROR_x03, "expression syntax error"},
  {ERROR_x04, "variable undeclaration"},
  {ERROR_x05, "while statement must have od"},
  {ERROR_x06, "while statement must have do"},
  {ERROR_x07, "if statement must have fi"},
  {ERROR_x08, "expect ("},
  {ERROR_x09, "missing )"},
  {ERROR_x10, "declaration missing ','"},
  {ERROR_x11, "unknown mistake"},
  {ERROR_x12, "if statement must have else"},
  {ERROR_x13, "if statement must have then"},
  {ERROR_x14, "expect ':='"},
  {ERROR_x15, "expect 'read' keyword"},
  {ERROR_x16, "expect 'write' keyword"},
  {ERROR_x17, "expect '~'"},
  {ERROR_x18, "expect 'while' keyword"},
  {ERROR_x19, "expect 'if' keyword"},
  {ERROR_x20, "expect 'skip' keyword"},
  {ERROR_x21, "expect a arithmetic operators such as '+','-','*','/'"},
  {ERROR_x22, "expect a relational operator such as '=' and '<'"},
  {ERROR_x23, "expect a decimial int number"},
};

/**
 * @brief 
 * printf specific error infomation
 * @param erroinfo 
 */
void Log(int errorkind, int row, int col) {
  printf(RED"[error]:%s at positon (%d,%d)\n"NONE,errors[errorkind].str,row, col);
  exit(-1);
  //printf("%s\n", errors[errorkind].str);
}

void Print(char *str){
  printf(BLUE"[info] "NONE);
  printf("%s\n",str);
}

void Assert(char* errinfo) {
  assert(errinfo);
}

// more TODO

#endif