#ifndef _HELPER_
#define _HELPER_

#include "defs.h"
#include "error.c"
#include "sys.c"

/**
 * @brief 
 * Put the pre-recognized token back into the tokens array
 * @param t 
 */
void putback(Token_t t) {
  put_token = t;
}

/**
 * @brief Get the token object
 * return the next token in tokens array
 * @return Token_t
 */
Token_t get_token() {
  Token_t t;
  if (put_token.type != -1) {
    t = put_token;
    put_token.type = -1;
    return t;
  }
  t = tokens[p_token];
  // printf("the p_token is => %d ,hit the token => %d, the next token is => %d\n",p_token,tokens[p_token].type,tokens[p_token+1].type);
  ++p_token;
  return t;
}

/**
 * @brief
 * printf the parse error infomation
 * the errorinfo is set by specific parse_xxx() function
 */
void handle_error(int errorkind, int row, int col) {
  Log(errorkind, row, col);
}

/**
 * @brief 
 * compare hold token and expected token type 
 * return 0 on successful
 * exit(-1) on failure
 * @param t 
 * @param type 
 * @return int 
 */
int match(Token_t hold, int expected) {
  switch (expected) {
    case TK_SEMI:
      if (hold.type == TK_SEMI) {
        Print("token ';' parsing via!");
        break;
      } else {
        // Print("match error! expect ';'");
        handle_error(ERROR_x00,hold.row,hold.col);
        break;
      }
    case TK_NUM:
      if (hold.type == TK_NUM) {
        Print("token 'num' parsing via!");
        break;
      } else {
        // Print("match error! expect ';'");
        handle_error(ERROR_x23,hold.row,hold.col);
        break;
      }
    case TK_IDENTIFIER:
      if (serchslot(hold.str) != -1 && hold.type == TK_IDENTIFIER) {
        Print("token identifier parsing via!");
        break;
      } else {
        handle_error(ERROR_x04,hold.row,hold.col);
        break;
      }
    case TK_SKIP:
      if (hold.type == TK_SKIP) {
        Print("token 'skip' parsing via!");
        break;
      } else {
        handle_error(ERROR_x20,hold.row,hold.col);
        break;
      }
    case TK_COMMA:
      if (hold.type == TK_COMMA) {
        Print("token ',' parsing via!");
        break;
      } else {
        handle_error(ERROR_x10,hold.row,hold.col);
        break;
      }
    case TK_ASSIGN:
      if (hold.type == TK_ASSIGN) {
        Print("token ':=' parsing via!");
        break;
      } else {
        handle_error(ERROR_x14,hold.row,hold.col);
        break;
        break;
      }
    case TK_LP:
      if (hold.type == TK_LP) {
        Print("token '(' parsing via!");
        ++left_parentheses_cnt;
        break;
      } else {
        handle_error(ERROR_x08,hold.row,hold.col);
        break;
      }
    case TK_RP:
      if (hold.type == TK_RP) {
        Print("token ')' parsing via!");
        ++right_parentheses_cnt;
        break;
      } else {
        handle_error(ERROR_x09,hold.row,hold.col);
        break;
      }
    case TK_READ:
      if (hold.type == TK_READ) {
        Print("token 'read' parsing via!");
        break;
      } else {
        handle_error(ERROR_x15,hold.row,hold.col);
        break;
      }
    case TK_WRITE:
      if (hold.type == TK_WRITE) {
        Print("token 'write' parsing via!");
        break;
      } else {
        handle_error(ERROR_x16,hold.row,hold.col);
        break;
      }
    case TK_WHILE:
      if (hold.type == TK_WHILE) {
        Print("token 'while' parsing via!");
        break;
      } else {
        handle_error(ERROR_x18,hold.row,hold.col);
        break;
      }
    case TK_IF:
      if (hold.type == TK_IF) {
        Print("token 'if' parsing via!");
        break;
      } else {
        handle_error(ERROR_x19,hold.row,hold.col);
        break;
      }
    case TK_NOT:
      if (hold.type == TK_NOT) {
        Print("token '~' parsing via!");
        break;
      } else {
        handle_error(ERROR_x17,hold.row,hold.col);
        break;
      }
    default:
      Print("no recognize token type!");
      break;
  }
  return (0);
}

/**
 * @brief
 * judge : the identifier is a keyword
 * if it is a keyword then return it's token type
 * if not return -1
 * @param str
 * @return int
 */
int id_iskeyword(char* str) {
  for (int i = 0; i < ARRLEN(keyword_table); ++i) {
    if (!strcmp(keyword_table[i], str)) {
      return TK_VAR + i;
      break;
    }
  }
  return (-1);
}

#endif