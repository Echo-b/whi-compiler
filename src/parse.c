#ifndef _PARSE_
#define _PARSE_

#include "parse.h"
#include "defs.h"
#include "generate_instr.c"
#include "helper.c"

/**
 * @brief 
 * X ::= var V {',' V}
 * parse variable definite
 * nothing on successful
 * call handle_error() function on unsuccessful 
 */
void parse_vardeclation(){
  Token_t hold_token = tokens[p_token];
  match(hold_token,TK_VAR);
  hold_token = get_token();
  match(hold_token,TK_IDENTIFIER);
  hold_token = get_token();
  if(hold_token.type == TK_COMMA){
    while(hold_token.type != TK_SEMI){
      match(hold_token, TK_COMMA);
      hold_token = get_token();
      match(hold_token, TK_IDENTIFIER);
      hold_token = get_token();
    }
  }else {
    return;
  }
}

/**
 * @brief 
 * E ::= T[TS]
 * parse expression such as if,while and so on
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_expression(){
  parse_subexpression_T();
  Token_t hold_token = tokens[p_token];
  if(hold_token.type == TK_PLUS || hold_token.type == TK_MINUS){
    parse_subexpression_TS();
    hold_token = get_token();
  }
  else
    handle_error(ERROR_x11);
}


/**
 * @brief 
 * TS ::= '+'T[TS] | '-'T[TS]
 * nothing on successful
 * call handle_error() function on unsuccessful 
 */
void parse_subexpression_TS(){
  Token_t hold_token = tokens[p_token];
  switch (hold_token.type)
  {
  hold_token = get_token();
  case TK_PLUS:
    hold_token = get_token(); // skip + token
    parse_subexpression_T();
    hold_token = tokens[p_token];
    if(hold_token.type == TK_PLUS || hold_token.type == TK_MINUS)
      parse_subexpression_TS();
    else
      handle_error(ERROR_x11);
    break;
  case TK_MINUS:
    hold_token = get_token(); // skip - token
    parse_subexpression_T();
    hold_token = tokens[p_token];
    if(hold_token.type == TK_PLUS || hold_token.type == TK_MINUS)
      parse_subexpression_TS();
    else
      handle_error(ERROR_x11);
    break;
  default:
    handle_error(ERROR_x11);
    break;
  }
  hold_token = get_token();
}

/**
 * @brief 
 * T ::= F[FS]
 * nothing on successful
 * call handle_error() function on unsuccessful 
 */
void parse_subexpression_T(){
  parse_subexpression_F();
  Token_t hold_token = tokens[p_token];
  if(hold_token.type == TK_MUL || hold_token.type == TK_DIV){
    parse_subexpression_FS();
    hold_token = get_token();
  }
  else
    handle_error(10);
}

/**
 * @brief 
 * FS ::= '*'F[FS] | '-'F[FS]
 * nothing on successful
 * call handle_error() function on unsuccessful 
 */
void parse_subexpression_FS(){
  Token_t hold_token = tokens[p_token];
  switch (hold_token.type)
  {
  hold_token = get_token();
  case TK_MUL:
    hold_token = get_token();   //skip * token
    parse_subexpression_F();
    hold_token = tokens[p_token];
    if(hold_token.type == TK_MUL || hold_token.type == TK_DIV)
      parse_subexpression_FS();
    else
      handle_error(ERROR_x11);
    break;
  case TK_DIV:
    hold_token = get_token();  // skip / token
    parse_subexpression_F();
    hold_token = tokens[p_token];
    if(hold_token.type == TK_MUL || hold_token.type == TK_DIV)
      parse_subexpression_FS();
    else
      handle_error(ERROR_x11);
    break;
  default:
    handle_error(ERROR_x11);
    break;
  }
  hold_token = get_token();
}

/**
 * @brief 
 * F ::= D[D1]
 * nothing on successful
 * call handle_error() function on unsuccessful 
 */
void parse_subexpression_F(){
  parse_subexpression_D();
  Token_t hold_token = tokens[p_token];
  if(hold_token.type == TK_EQ || hold_token.type == TK_LESS){
    parse_subexpression_D1();
    hold_token = get_token();
  }
  else
    handle_error(ERROR_x11);
}

/**
 * @brief 
 * D1 ::= '='D | '<'D
 * nothing on successful
 * call handle_error() function on unsuccessful 
 */
void parse_subexpression_D1(){
  Token_t hold_token = tokens[p_token];
  if(hold_token.type == TK_EQ || hold_token.type == TK_LESS){
    hold_token = get_token(); // skip '=' or '<' token
    parse_subexpression_D();
    hold_token = get_token();
  }
  else
    handle_error(ERROR_x11);
}

/**
 * @brief 
 * D ::= N | V | (E) | ~E
 * nothing on successful
 * call handle_error() function on unsuccessful 
 */
void parse_subexpression_D(){
  Token_t hold_token = tokens[p_token];
  switch (hold_token.type)
  {
  case TK_NUM:
    match(hold_token,TK_NUM);
    break;
  case TK_IDENTIFIER:
    match(hold_token,TK_IDENTIFIER);
    break;
  case TK_LP:
    hold_token = get_token(); // skip (
    parse_expression();
    hold_token = tokens[p_token];
    match(hold_token,TK_RP); // match )
    break;
  case TK_NOT:
    hold_token = get_token(); // skip ~
    parse_expression();
    break;
  default:
    handle_error(ERROR_x11);
    break;
  }
  hold_token = get_token();
}

/**
 * @brief 
 * parse skip statement and generate the nop instr
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_skip_stmt(){
  Token_t hold_token = tokens[p_token];
  match(hold_token, TK_SKIP);
  hold_token = get_token(); 
}

/**
 * @brief 
 * V := E
 * parse assign statement(x:=y)
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_assg_stmt(){
  Token_t hold_token = tokens[p_token];
  match(hold_token, TK_IDENTIFIER);
  hold_token = get_token();
  match(hold_token, TK_ASSIGN);
  hold_token = get_token();
  parse_expression();
  hold_token = get_token();
}

/**
 * @brief 
 * parse  read statement and generate read instr
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_read_stmt(){
   Token_t hold_token = get_token(); // skip read keyword
  match(hold_token, TK_LP);
  hold_token = get_token();
  match(hold_token, TK_IDENTIFIER);
  hold_token = get_token();
  match(hold_token, TK_RP);
  hold_token = get_token(); 
}

/**
 * @brief 
 * parse write statement and generate write instr
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_write_stmt(){
  Token_t hold_token = get_token(); // skip write keyword
  match(hold_token, TK_LP);
  hold_token = get_token();
  parse_expression();
  match(hold_token, TK_RP);
  hold_token = get_token(); 
}

/**
 * @brief 
 * parse if statement
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_if_stmt(){
  Token_t hold_token = get_token();  //skip if keyword
  parse_expression();
  hold_token = tokens[p_token];
  if (TK_THEN == hold_token.type) {
    hold_token = get_token(); // skip then keyword
    parse_stmt_list();
    hold_token = tokens[p_token];
    if (TK_ELSE == hold_token.type) {
      hold_token = get_token(); // skip else keyword
      parse_stmt_list();
      hold_token = tokens[p_token];
      if (TK_FI == hold_token.type) {
        hold_token = get_token();
      } else {
        handle_error(ERROR_x07);  // lack fi
      }
    } else {
      handle_error(ERROR_x12);  // lack else
    }
  } else {
    handle_error(ERROR_x13);  // lack then
  }
}

/**
 * @brief 
 * parse while statement
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_while_stmt(){
  Token_t hold_token = get_token(); // skip while keyword
  parse_expression();
  if (TK_DO == hold_token.type) {
    hold_token = get_token(); // skip do keyword
    parse_stmt_list();
    hold_token = tokens[p_token];
    if (TK_OD == hold_token.type) {
      hold_token = get_token(); // skip od keyword
    } else {
      handle_error(ERROR_x05); // lack od
    }
  } else {
    handle_error(ERROR_x06); // lack do
  }
}

/**
 * @brief 
 * parse statement 
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_statement(){
  Token_t hold_token = tokens[p_token];
  if (TK_SKIP == hold_token.type)
    parse_skip_stmt();
  else if (TK_IDENTIFIER == hold_token.type)
    parse_assg_stmt();
  else if (TK_IF == hold_token.type)
    parse_if_stmt();
  else if (TK_WHILE == hold_token.type)
    parse_while_stmt();
  else if (TK_READ == hold_token.type)
    parse_read_stmt();
  else if (TK_WRITE == hold_token.type)
    parse_write_stmt();
  else
    handle_error(10);
}

/**
 * @brief 
 * parse statement list
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_stmt_list(){
  parse_statement();
  Token_t hold_token = get_token();
  if (TK_SEMI == hold_token.type) {
    hold_token = get_token(); // skip ;
    parse_stmt_list();
    hold_token = get_token();
  } else {
    return;
  }
}

/**
 * @brief 
 * parse program 
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_program(){
  Token_t hold_token = get_token();
  if (TK_VAR == hold_token.type) {
    parse_vardeclation();
    hold_token = get_token();
    match(hold_token, TK_SEMI);
    parse_stmt_list();
  } else {
    parse_stmt_list();
  }
  hold_token = get_token();
}

/**
 * @brief 
 * call parse_program() function and match the TK_EOF token
 * return 0 on successful
 * return -1 on failure
 * @return int 
 */
int parse(){
  parse_program();
  if(tokens[p_token].type == TK_EOF){
    printf("parse over, congratulations!!!");
    return 0;
  }else {
    handle_error(10);
  }
}

#endif