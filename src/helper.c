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
 * @brief Set the errorinfo object
 * if we hit a error then we call set_errorinfo() to set it
 * and call specific handle_error() function to handle it
 * @param info 
 */
void set_errorinfo(char* info) {
  strcpy(errinfo, info);
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
  t = tokens[parse_index];
  ++parse_index;
  return t;
}

/**
 * @brief
 * printf the parse error infomation
 * the errorinfo is set by specific parse_xxx() function
 */
void handle_error() {
  Log(errinfo);
}

/**
 * @brief 
 * compare t and expected token type 
 * return 0 on successful
 * exit(-1) on failure
 * @param t 
 * @param type 
 * @return int 
 */
int match(Token_t t, int type) {
  // char instr[8] = {'\0'};
  printf("token ====> %d\n", t.type);
  switch (type) {
    case TK_VAR:
      if (t.type == TK_VAR) {
        printf("token var recognize!\n");
        break;
      } else {
        printf("match error!\n");
        return (-1);
      }
    case TK_SEMI:
      if (t.type == TK_SEMI) {
        printf("token ';' recognize!\n");
        break;
      } else {
        printf("match error!\n");
        return (-1);
      }
    case TK_IDENTIFIER:
      if (t.type == TK_IDENTIFIER) {
        printf("token identifier recognize!\n");
        break;
      } else {
        printf("match error!\n");
        return (-1);
      }
    case TK_COMMA:
      if (t.type == TK_COMMA) {
        printf("token ',' recognize!\n");
        break;
      } else {
        printf("match error!\n");
        return (-1);
      }
    case TK_LP:
      if (t.type == TK_LP) {
        break;
      } else {
        printf("match error!\n");
        return (-1);
      }
    case TK_RP:
      if (t.type == TK_RP) {
        break;
      } else {
        printf("match error!\n");
        return (-1);
      }
    case TK_READ:
      if (t.type == TK_READ) {
        break;
      } else {
        printf("match error!\n");
        return (-1);
      }
    case TK_ASSIGN:
      if (t.type == TK_ASSIGN) {
        break;
      } else {
        printf("match error!\n");
        return (-1);
      }
    default:
      printf("no recognize token type!\n");
      break;
  }
  // ++parse_index;
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