#ifndef _PARSE_
#define _PARSE_

#include "parse.h"
#include "defs.h"
#include "generate_instr.c"
#include "helper.c"
#include "color.h"

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
      if(hold_token.type == TK_READ)
        break;
    }
    putback(hold_token);
    // printf("token type %d\n",hold_token.type);
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
  // printf("Parse_TS hold_token is %d\n",hold_token.type);
  switch (hold_token.type)
  {
  case TK_PLUS:
    Print("token '+' parsing via");
    hold_token = get_token(); // skip + token
    parse_subexpression_T();
    // generate_instr_add();
    hold_token = tokens[p_token];
    if(hold_token.type == TK_PLUS || hold_token.type == TK_MINUS){
      parse_subexpression_TS();
      break;
    }
    else
      // handle_error(ERROR_x11,hold_token.row,hold_token.col);
      break;
  case TK_MINUS:
    Print("token '-' parsing via");
    hold_token = get_token(); // skip - token
    parse_subexpression_T();
    // generate_instr_sub();
    hold_token = tokens[p_token];
    if(hold_token.type == TK_PLUS || hold_token.type == TK_MINUS){
      parse_subexpression_TS();
      break;
    }
    else
      // handle_error(ERROR_x11,hold_token.row,hold_token.col);
      break;
  default:
    handle_error(ERROR_x21,hold_token.row,hold_token.col);
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
    // Print("recognize '*' or '/' token");
    parse_subexpression_FS();
    // Print("quit parse_FS p_token type ******** %d",tokens[p_token].type);
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
    Print("token '*' parsing via");
    hold_token = get_token();   //skip * token
    parse_subexpression_F();
    // generate_instr_mul();
    hold_token = tokens[p_token];
    if(hold_token.type == TK_MUL || hold_token.type == TK_DIV){
      parse_subexpression_FS();
      break;
    }
    else
      break;
  case TK_DIV:
    Print("token '/' parsing via");
    hold_token = get_token();  // skip / token
    parse_subexpression_F();
    // generate_instr_div();
    // Print("after the parse_F, the p_token is===%d",p_token);
    hold_token = tokens[p_token];
    if(hold_token.type == TK_MUL || hold_token.type == TK_DIV){
      parse_subexpression_FS();
      break;
    }
    else
      // handle_error(ERROR_x11,hold_token.row,hold_token.col);
     break;
  default:
    handle_error(ERROR_x21,hold_token.row,hold_token.col);
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
  // Print("p_token ******** %d, token type=> %d",p_token,hold_token.type);
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
    if(hold_token.type == TK_EQ)
      Print("token '=' parsing via");
    else 
      Print("token '<' parsing via");
    hold_token = get_token(); // skip '=' or '<' token
    // may be more consideration
    parse_subexpression_D();
    // generate_instr_equ();
    // hold_token = get_token();
  }
  else
    handle_error(ERROR_x22,hold_token.row,hold_token.col);
}

/**
 * @brief 
 * D ::= N | V | (E) | ~E
 * nothing on successful
 * call handle_error() function on unsuccessful 
 */
void parse_subexpression_D(){
  Token_t hold_token = tokens[p_token];
  // Print("Parse_D token is %d\n",hold_token.type);
  switch (hold_token.type)
  {
  case TK_NUM:
    // generate_instr_lit(atoi(hold_token.str));
    match(hold_token,TK_NUM);
    break;
  case TK_IDENTIFIER:
    // generate_instr_lod(hold_token);
    match(hold_token,TK_IDENTIFIER);
    break;
  case TK_LP:
    match(hold_token,TK_LP);  // match (
    hold_token = get_token(); // skip (
    parse_expression();
    hold_token = tokens[p_token];
    match(hold_token,TK_RP); // match )
    break;
  case TK_NOT: 
    match(hold_token,TK_NOT);  
    hold_token = get_token(); // skip ~
    parse_expression();
    return;  // prevent call twice get_token() function
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
  Token_t gen_token = hold_token;
  match(hold_token, TK_IDENTIFIER);
  hold_token = get_token();
  match(hold_token, TK_ASSIGN);
  parse_expression();
  // generate_instr_sto(gen_token);
}

/**
 * @brief 
 * parse  read statement and generate read instr
 * read(V)
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_read_stmt(){
  Token_t hold_token = get_token(); // get read keyword
  match(hold_token,TK_READ);
  hold_token = get_token();
  match(hold_token, TK_LP);
  hold_token = get_token();
  // generate_instr_read(hold_token);
  match(hold_token, TK_IDENTIFIER);
  hold_token = get_token();
  match(hold_token, TK_RP);
  // Print("p_token ******** %d, token type=> %d",p_token,hold_token.type);
}

/**
 * @brief 
 * parse write statement and generate write instr
 * write(E)
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
  // generate_instr_wrt();
  hold_token = tokens[p_token];
  // Print("over the call the token type is %d\n",hold_token.type);
  match(hold_token, TK_RP);
  hold_token = get_token(); 
}

/**
 * @brief 
 * parse if statement
 * if E then L else L fi
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_if_stmt(){
  Token_t hold_token = tokens[p_token];
  match(hold_token,TK_IF);
  hold_token = get_token();  //skip if keyword
  parse_expression();
  hold_token = tokens[p_token];
  if (TK_THEN == hold_token.type) {
    Print("token 'then' parsing via");
    hold_token = get_token(); // skip then keyword
    parse_stmt_list();
    hold_token = tokens[p_token];
    if (TK_ELSE == hold_token.type) {
      Print("token 'else' parsing via");
      hold_token = get_token(); // skip else keyword
      parse_stmt_list();
      hold_token = tokens[p_token];
      if (TK_FI == hold_token.type) {
        Print("token 'fi' parsing via");
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
 * while E do L od
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_while_stmt(){
  // printf(BLUE"the instr_cnt is %d"NONE,instr_cnt);
  // int instr_start = instr_cnt;
  Token_t hold_token = tokens[p_token];
  match(hold_token,TK_WHILE);
  hold_token = get_token(); // skip while keyword
  parse_expression();
  hold_token = tokens[p_token];
  if (TK_DO == hold_token.type) {
    Print("token 'do' parsing via");
    hold_token = get_token(); // skip do keyword
    parse_stmt_list();
    hold_token = tokens[p_token];
    if (TK_OD == hold_token.type) {
      Print("token 'od' parsing via");
      // generate_instr_jmp(instr_start);
      // printf(BLUE"the instr_cnt is %d\n"NONE,instr_cnt);
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
  // Print("token type ===== %d",hold_token.type);
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
 * P ::= X[';'L]
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
  if(tokens[p_token].type == TK_EOF && !parse_flag){
    printf(GREEN"[success] parse over, congratulations!!!\n"NONE);
    return 0;
  }else {
    handle_error(ERROR_x24,tokens[p_token].row,tokens[p_token].col);
    return -1;
  }
}

#endif