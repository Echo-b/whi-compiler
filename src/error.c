#ifndef _ERROR_
#define _ERROR_
#include <assert.h>
#include <stdio.h>
#include "defs.h"
#include "color.h"

extern void putback(Token_t t);
extern Token_t get_token();

struct grammer_error{
  int errorkind;
  const char* str;
  // void (*handler) (int errorkind, int row, int col);
} errors[] = {
  {ERROR_x00, "missing ;"},
  {ERROR_x01, "missing :="},
  {ERROR_x02, "division by zero"},
  {ERROR_x03, "expression syntax error"},
  {ERROR_x04, "variable undeclaration"},
  {ERROR_x05, "while statement must have od"},
  {ERROR_x06, "while statement must have do"},
  {ERROR_x07, "if statement must have fi"},
  {ERROR_x08, "missing ("},
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
  {ERROR_x24, "program aborted unexpectedly, exited with -1"},
  {ERROR_x25, "extra ';'"},
  {ERROR_x26, "extra ','"},
  {ERROR_x27, "extra ("},
  {ERROR_x28, "extra )"},
  {ERROR_x29, "there must be a variable inside the parentheses"},
  {ERROR_x30, "only one variable within the parentheses of a read expression"},
  {ERROR_x31, "operator is required between two identifiers"},
  {ERROR_x32, "operator is required between two num"},
  {ERROR_x33, "continuous operator"},
};

/**
 * @brief 
 * printf specific error infomation
 * @param erroinfo 
 */
void Log(int errorkind, int row, int col) {
  if(errorkind == ERROR_x24)
    printf(RED"[error] %s \n"NONE,errors[errorkind].str);
  else
    printf(RED"[error] %s at positon (%d,%d)\n"NONE,errors[errorkind].str,row, col);
  parse_flag = 1;
}

void handle_missing(int errorkind,int row,int col){
  Log(errorkind,row,col);
  Token_t add_token;
  add_token.row = row;
  add_token.col = col; 
  switch (errorkind)
  {
  case ERROR_x10:
    add_token.type = TK_COMMA;
    break;
  case ERROR_x00:
    add_token.type = TK_SEMI;
    break;
  case ERROR_x01:
    add_token.type = TK_ASSIGN;
    break;
  case ERROR_x13:
    add_token.type = TK_THEN;
    break;
  case ERROR_x12:
    add_token.type = TK_ELSE;
    break;
  case ERROR_x07:
    add_token.type = TK_FI;
    break;
  case ERROR_x06:
    add_token.type = TK_DO;
    break;
  case ERROR_x05:
    add_token.type = TK_OD;
    break;
  case ERROR_x08:
    add_token.type = TK_LP;
    break;
  case ERROR_x09:
    add_token.type = TK_RP;
    break;
  case ERROR_x29:
    add_token.type = TK_IDENTIFIER;
    break;
  default:
    break;
  }
  putback(add_token);
}

void handle_extra(int errorkind, int row, int col){
  Log(errorkind,row,col);
  get_token();
}

void Print(char *str){
  printf(BLUE"[info] "NONE);
  printf("%s\n",str);
}

// more TODO

#endif