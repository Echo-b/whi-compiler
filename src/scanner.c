#ifndef _SCANNER_
#define _SCANNER_

#include "defs.h"
#include "helper.c"
#include "sys.c"

static regex_t re[NR_REGEX] = {};

/**
 * @brief 
 * Construct the string into a standard
 * regularization expression structure
 * nothing on successful
 * call regerror() on failure
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (int i = 0; i < NR_REGEX; ++i) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      printf("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

/**
 * @brief 
 * recognize token and store it in the tokens array
 * and if the token is a keyword then call addglob() function 
 * to add it to the global symbol table 
 * return true on successful
 * return false on failure
 * @param e 
 * @return true 
 * @return false 
 */
static bool make_token(char* e) {
  int position = 0;
  regmatch_t pmatch;
  int i;
  while (e[position] != '\0') {
    for (i = 0; i < NR_REGEX; ++i) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char* substr_start = e + position;
        int substr_len = pmatch.rm_eo;
        printf("match rules[%d] = \"%s\" at position %d with len %d: %.*s\n",
               i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        switch (rules[i].token_type) {
          case TK_NOTYPE:
            break;
          case TK_EQ:
          case TK_PLUS:
          case TK_MINUS:
          case TK_MUL:
          case TK_DIV:
          case TK_NOT:
          case TK_LESS:
          case TK_LP:
          case TK_RP:
          case TK_SEMI:
          case TK_ASSIGN:
          case TK_COMMA:
            tokens[nr_token].type = rules[i].token_type;
            if (tokens[nr_token].type == TK_SEMI)
              add_gsyt_flag = 0;
            tokens[nr_token].precedence = rules[i].precedence;
            tokens[nr_token].row = row;
            tokens[nr_token].col = position - substr_len;
            nr_token++;
            break;
          case TK_NUM:
            tokens[nr_token].precedence = rules[i].precedence;
            if (substr_len > 32)
              return false;
            bzero(tokens[nr_token].str, 0);
            strncpy(tokens[nr_token].str, substr_start, substr_len);
            tokens[nr_token].type = rules[i].token_type;
            tokens[nr_token].row = row;
            tokens[nr_token].col = position - substr_len;
            nr_token++;
            break;
          case TK_IDENTIFIER:
            tokens[nr_token].precedence = rules[i].precedence;
            if (substr_len > 32)
              return false;
            bzero(tokens[nr_token].str, 0);
            strncpy(tokens[nr_token].str, substr_start, substr_len);

            // judge => the identifier is a keyword?
            int ret;
            if ((ret = id_iskeyword(tokens[nr_token].str)) != -1) {
              if (ret == TK_VAR)
                add_gsyt_flag = 1;
              tokens[nr_token].type = ret;
            } else {
              tokens[nr_token].type = rules[i].token_type;
              if (add_gsyt_flag == 1) {
                if (addglob(tokens[nr_token].str) == -1)
                  return (-1);
              }
            }
            tokens[nr_token].row = row;
            tokens[nr_token].col = position - substr_len;
            nr_token++;
            break;
          default:;
        }
        break;
      }
    }
    if (i == NR_REGEX) {
      printf("the definition at position %d error\n%s\n%*.s^\n", position, e, position, "");
      exit(-1);
    }
  }
  return true;
}

/**
 * @brief 
 * read a string e and recognize all tokens in it
 * if successful set success = true and return 0
 * if failure set success = false and return 0
 * @param e 
 * @param success 
 * @return int 
 */
int init_token(char* e, bool* success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  ++row;
  *success = true;
  return 0;
}

/**
 * @brief 
 * display the tokens array that we call init_token() function to recognize
 */
void show_token() {
  for (int i = 0; i < nr_token; i++) {
    printf("token[%d] type=> [%d] \t token value => [%s] \t position =>(%d,%d)\n",i ,tokens[i].type, tokens[i].str, tokens[i].row, tokens[i].col);
  }
}

#endif