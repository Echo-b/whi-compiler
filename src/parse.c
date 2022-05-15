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
  // generate_instr_int(Gsyspos);
  Token_t hold_token = get_token(); // skip var keyword
  match(hold_token,TK_IDENTIFIER);
  // generate_instr_var(hold_token);
  hold_token = get_token();
  if(hold_token.type == TK_COMMA){
    while(hold_token.type != TK_SEMI){
      match(hold_token, TK_COMMA);
      hold_token = get_token();
      match(hold_token, TK_IDENTIFIER);
      // generate_instr_var(hold_token);
      hold_token = get_token();
    }
    putback(hold_token);
    printf("token type %d\n",hold_token.type);
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
    // hold_token = get_token();
  }
  else
    return;
    // handle_error(ERROR_x11,hold_token.row,hold_token.col);
}


/**
 * @brief 
 * TS ::= '+'T[TS] | '-'T[TS]
 * nothing on successful
 * call handle_error() function on unsuccessful 
 */
void parse_subexpression_TS(){
  Token_t hold_token = tokens[p_token];
  printf("Parse_TS hold_token is %d\n",hold_token.type);
  switch (hold_token.type)
  {
  case TK_PLUS:
    hold_token = get_token(); // skip + token
    parse_subexpression_T();
    hold_token = tokens[p_token];
    if(hold_token.type == TK_PLUS || hold_token.type == TK_MINUS){
      parse_subexpression_TS();
      break;
    }
    else
      // handle_error(ERROR_x11,hold_token.row,hold_token.col);
      break;
  case TK_MINUS:
    hold_token = get_token(); // skip - token
    parse_subexpression_T();
    hold_token = tokens[p_token];
    if(hold_token.type == TK_PLUS || hold_token.type == TK_MINUS){
      parse_subexpression_TS();
      break;
    }
    else
      // handle_error(ERROR_x11,hold_token.row,hold_token.col);
      break;
  default:
    handle_error(ERROR_x11,hold_token.row,hold_token.col);
    break;
  }
  // hold_token = get_token();
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
    // printf("recognize '*' or '/' token\n");
    parse_subexpression_FS();
    printf("quit parse_FS p_token type ******** %d\n",tokens[p_token].type);
    // hold_token = get_token();
  }
  else
    return;
    // handle_error(ERROR_x11,hold_token.row,hold_token.col);
}

/**
 * @brief 
 * FS ::= '*'F[FS] | '/'F[FS]
 * nothing on successful
 * call handle_error() function on unsuccessful 
 */
void parse_subexpression_FS(){
  Token_t hold_token = tokens[p_token];
  switch (hold_token.type)
  {
  case TK_MUL:
    printf("recognize '*' token\n");
    hold_token = get_token();   //skip * token
    parse_subexpression_F();
    hold_token = tokens[p_token];
    if(hold_token.type == TK_MUL || hold_token.type == TK_DIV){
      parse_subexpression_FS();
      break;
    }
    else
      break;
  case TK_DIV:
    printf("recognize '/' token\n");
    hold_token = get_token();  // skip / token
    parse_subexpression_F();
    printf("after the parse_F, the p_token is===%d\n",p_token);
    hold_token = tokens[p_token];
    if(hold_token.type == TK_MUL || hold_token.type == TK_DIV){
      parse_subexpression_FS();
      break;
    }
    else
      // handle_error(ERROR_x11,hold_token.row,hold_token.col);
     break;
  default:
    handle_error(ERROR_x11,hold_token.row,hold_token.col);
    break;
  }
  // hold_token = get_token();
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
  printf("p_token ******** %d, token type=> %d\n",p_token,hold_token.type);
  if(hold_token.type == TK_EQ || hold_token.type == TK_LESS){
    parse_subexpression_D1();
    // hold_token = get_token();
  }
  else
    return;
    // handle_error(ERROR_x11,hold_token.row,hold_token.col);
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
    printf("recognize '=' token \n");
    hold_token = get_token(); // skip '=' or '<' token
    // may be more consideration
    parse_subexpression_D();
    // hold_token = get_token();
  }
  else
    handle_error(ERROR_x11,hold_token.row,hold_token.col);
}

/**
 * @brief 
 * D ::= N | V | (E) | ~E
 * nothing on successful
 * call handle_error() function on unsuccessful 
 */
void parse_subexpression_D(){
  Token_t hold_token = tokens[p_token];
  printf("Parse_D token is %d\n",hold_token.type);
  switch (hold_token.type)
  {
  case TK_NUM:
    match(hold_token,TK_NUM);
    break;
  case TK_IDENTIFIER:
    match(hold_token,TK_IDENTIFIER);
    break;
  case TK_LP:
    match(hold_token,TK_LP);  // match (
    hold_token = get_token(); // skip (
    parse_expression();
    hold_token = tokens[p_token];
    match(hold_token,TK_RP); // match )
    return;
  case TK_NOT: 
    printf("recognize '~' token\n");
    hold_token = get_token(); // skip ~
    parse_expression();
    break;
  default:
    handle_error(ERROR_x11,hold_token.row,hold_token.col);
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
  Token_t hold_token = get_token();
  match(hold_token, TK_IDENTIFIER);
  hold_token = get_token();
  match(hold_token, TK_ASSIGN);
  parse_expression();
  // hold_token = get_token();
  // printf("p_token $$$$$$$$$$$$$$$%d\n",p_token);
}

/**
 * @brief 
 * parse  read statement and generate read instr
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_read_stmt(){
  Token_t hold_token = get_token(); // get read keyword
  match(hold_token,TK_READ);
  hold_token = get_token();
  match(hold_token, TK_LP);
  hold_token = get_token();
  match(hold_token, TK_IDENTIFIER);
  hold_token = get_token();
  match(hold_token, TK_RP);
  // hold_token = get_token(); 
  printf("p_token ******** %d, token type=> %d\n",p_token,hold_token.type);
}

/**
 * @brief 
 * parse write statement and generate write instr
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_write_stmt(){
  Token_t hold_token = get_token(); // get write keyword
  match(hold_token,TK_WRITE);
  hold_token = get_token();
  match(hold_token, TK_LP);
  // hold_token = get_token();
  parse_expression();
  hold_token = tokens[p_token];
  printf("over the call the token type is %d\n",hold_token.type);
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
        handle_error(ERROR_x07,hold_token.row,hold_token.col);  // lack fi
      }
    } else {
      handle_error(ERROR_x12,hold_token.row,hold_token.col);  // lack else
    }
  } else {
    handle_error(ERROR_x13,hold_token.row,hold_token.col);  // lack then
  }
}

/**
 * @brief 
 * parse while statement
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_while_stmt(){
  Token_t hold_token = tokens[p_token];
  match(hold_token,TK_WHILE);
  hold_token = get_token(); // skip while keyword
  parse_expression();
  hold_token = tokens[p_token];
  if (TK_DO == hold_token.type) {
    printf("recognize 'do' token\n");
    hold_token = get_token(); // skip do keyword
    parse_stmt_list();
    hold_token = tokens[p_token];
    if (TK_OD == hold_token.type) {
      printf("recognize 'od' token\n");
      hold_token = get_token(); // skip od keyword
    } else {
      handle_error(ERROR_x05,hold_token.row,hold_token.col); // lack od
    }
  } else {
    handle_error(ERROR_x06,hold_token.row,hold_token.col); // lack do
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
    handle_error(ERROR_x11,hold_token.row,hold_token.col);
}

/**
 * @brief 
 * L ::= S[';'L]
 * parse statement list
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_stmt_list(){
  parse_statement();
  Token_t hold_token = tokens[p_token];
  printf("token type ===== %d\n",hold_token.type);
  if (TK_SEMI == hold_token.type) {
    match(hold_token, TK_SEMI);
    hold_token = get_token(); // skip ;
    parse_stmt_list();
    // hold_token = get_token();
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
    // printf("----------%d----------\n",p_token);
    hold_token = get_token();
    match(hold_token, TK_SEMI);
    parse_stmt_list();
  } else {
    parse_stmt_list();
  }
  // hold_token = get_token();
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
  // printf("p_token ** %d\n",tokens[p_token].type);
  if(tokens[p_token].type == TK_EOF){
    printf("parse over, congratulations!!!\n");
    return 0;
  }else {
    handle_error(ERROR_x11,tokens[p_token].row,tokens[p_token].col);
  }
}

#endif