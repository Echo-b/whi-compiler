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

  // missing comma 
  if(TK_IDENTIFIER == tokens[p_token].type){
    handle_missing(ERROR_x10,hold_token.row,hold_token.col);
  }
  
  hold_token = get_token();
  if(hold_token.type == TK_COMMA){
    while(hold_token.type != TK_SEMI){
      match(hold_token, TK_COMMA);

      // extra comma
      if(TK_COMMA == tokens[p_token].type){
        handle_extra(ERROR_x26,hold_token.row,hold_token.col);
      }

      hold_token = get_token();
      match(hold_token, TK_IDENTIFIER);
      // generate_instr_var(hold_token);

      // missing comma 
      if(TK_IDENTIFIER == tokens[p_token].type){
        handle_missing(ERROR_x10,hold_token.row,hold_token.col);
      }

      // missing semi colon
      if(TK_READ == tokens[p_token].type || TK_WHILE == tokens[p_token].type 
           || TK_WRITE == tokens[p_token].type || TK_IF == tokens[p_token].type 
           || TK_SKIP == tokens[p_token].type){
        handle_missing(ERROR_x00,hold_token.row,hold_token.col);
      }

      // only variable declaration statements  =====> normal parse
      if(TK_EOF == tokens[p_token].type){
        putback(tokens[p_token]);
        return;
      }

      hold_token = get_token();
  
      // only variable declaration statements and has a extra semi colon
      if(TK_EOF == tokens[p_token].type){
        handle_error(ERROR_x25,hold_token.row,hold_token.col);
        return;
      }
      // printf("token type is %d\n",hold_token.type);
    }
    putback(hold_token);
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
  }
  else
    return;
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
  case TK_PLUS:
    Print("token '+' parsing via");
    hold_token = get_token(); // skip + token

    // continuous operator
    if(TK_PLUS == tokens[p_token].type){
      handle_extra(ERROR_x33,hold_token.row,hold_token.col);
    }

    parse_subexpression_T();
    // generate_instr_add();
    hold_token = tokens[p_token];
    if(hold_token.type == TK_PLUS || hold_token.type == TK_MINUS){
      parse_subexpression_TS();
      break;
    }
    else
      break;
  case TK_MINUS:
    Print("token '-' parsing via");
    hold_token = get_token(); // skip - token

    // continuous operator
    if(TK_MINUS == tokens[p_token].type){
      handle_extra(ERROR_x33,hold_token.row,hold_token.col);
    }

    parse_subexpression_T();
    // generate_instr_sub();
    hold_token = tokens[p_token];
    if(hold_token.type == TK_PLUS || hold_token.type == TK_MINUS){
      parse_subexpression_TS();
      break;
    }
    else
      break;
  default:
    handle_error(ERROR_x21,hold_token.row,hold_token.col);
    break;
  }
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
  }
  else
    return;
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

    // continuous operator
    if(TK_MUL == tokens[p_token].type){
      handle_extra(ERROR_x33,hold_token.row,hold_token.col);
    }

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

    // continuous operator
    if(TK_DIV == tokens[p_token].type){
      handle_extra(ERROR_x33,hold_token.row,hold_token.col);
    }

    parse_subexpression_F();
    // generate_instr_div();

    hold_token = tokens[p_token];
    if(hold_token.type == TK_MUL || hold_token.type == TK_DIV){
      parse_subexpression_FS();
      break;
    }
    else
     break;
  default:
    handle_error(ERROR_x21,hold_token.row,hold_token.col);
    break;
  }
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
  }
  else
    return;
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

    // continuous operator
    if(TK_EQ == tokens[p_token].type || TK_LESS == tokens[p_token].type){
      handle_extra(ERROR_x33,hold_token.row,hold_token.col);
    }

    // may be more consideration
    parse_subexpression_D();
    // generate_instr_equ();
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
  switch (hold_token.type)
  {
  case TK_NUM:
    // generate_instr_lit(atoi(hold_token.str));
    match(hold_token,TK_NUM);

    // operator is required between two num
    if(TK_NUM == tokens[p_token + 1].type){
      handle_extra(ERROR_x32,hold_token.row,hold_token.col);
    }

    break;
  case TK_IDENTIFIER:
    // generate_instr_lod(hold_token);
    match(hold_token,TK_IDENTIFIER);

    // operator is required between two identifiers
    if(TK_IDENTIFIER == tokens[p_token + 1].type){
      handle_extra(ERROR_x31,hold_token.row,hold_token.col);
    }

    break;
  case TK_LP:
    match(hold_token,TK_LP);  // match (
    hold_token = get_token(); // skip (
    parse_expression();
    hold_token = tokens[p_token];

    // missing )
    if(TK_RP != hold_token.type){
      handle_missing(ERROR_x09,hold_token.row,hold_token.col);
      hold_token = get_token();
      putback(tokens[p_token]);
    }

    match(hold_token,TK_RP); // match )

    // extra )
    if(TK_RP == tokens[p_token + 1].type){
      if(left_parentheses_cnt != right_parentheses_cnt +1)
        handle_extra(ERROR_x28,tokens[p_token].row,tokens[p_token].col);
    }

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

  // missing :=
  if(TK_IDENTIFIER == tokens[p_token].type){
    handle_missing(ERROR_x01,hold_token.row,hold_token.col);
  }

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

  // missing (
  if(TK_LP != tokens[p_token].type){
    handle_missing(ERROR_x08,tokens[p_token].row,tokens[p_token].col);
  }

  hold_token = get_token();
  match(hold_token, TK_LP);

  // extra (
  if(TK_LP == tokens[p_token].type){
    handle_extra(ERROR_x27,tokens[p_token].row,tokens[p_token].col);
  }

  // missing identifier, there must be a variable inside the parentheses 
  if(TK_IDENTIFIER != tokens[p_token].type){
    handle_missing(ERROR_x29,tokens[p_token].row,tokens[p_token].col);
  }

  hold_token = get_token();
  // generate_instr_read(hold_token);
  match(hold_token, TK_IDENTIFIER);

  // extra identifier in parentheses
  if(TK_IDENTIFIER == tokens[p_token].type){
    handle_extra(ERROR_x30,tokens[p_token].row,tokens[p_token].col);
  }

  // missing )
  if(TK_RP != tokens[p_token].type){
    handle_missing(ERROR_x09,tokens[p_token].row,tokens[p_token].col);
  }

  hold_token = get_token();
  match(hold_token, TK_RP);

  // extra )
  if(TK_RP == tokens[p_token].type){
    handle_extra(ERROR_x28,tokens[p_token].row,tokens[p_token].col);
  }

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

   // missing (
  if(TK_LP != tokens[p_token].type){
    handle_missing(ERROR_x08,tokens[p_token].row,tokens[p_token].col);
  }

  hold_token = get_token();
  match(hold_token, TK_LP);

  parse_expression();
  // generate_instr_wrt();
  hold_token = tokens[p_token];

  // missing ) 
  if(TK_RP != tokens[p_token].type){
    handle_missing(ERROR_x09,tokens[p_token].row,tokens[p_token].col);
    hold_token = get_token();
    putback(tokens[p_token]);
  }

  match(hold_token, TK_RP);
  hold_token = get_token(); 

  // extra )
  if(TK_RP == tokens[p_token].type){
    if(right_parentheses_cnt + 1 != left_parentheses_cnt)
      handle_extra(ERROR_x28,tokens[p_token].row,tokens[p_token].col);
  }

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

  // missing then keyword
  if(TK_THEN != hold_token.type){
    handle_missing(ERROR_x13,hold_token.row,hold_token.col);
    hold_token = get_token();
    putback(tokens[p_token]);
  }

  if (TK_THEN == hold_token.type) {
    Print("token 'then' parsing via");
    hold_token = get_token(); // skip then keyword
    parse_stmt_list();
    hold_token = tokens[p_token];

    // missing else keyword
    if(TK_ELSE != hold_token.type){
      handle_missing(ERROR_x12,hold_token.row,hold_token.col);
      hold_token = get_token();
      putback(tokens[p_token]);
    }

    if (TK_ELSE == hold_token.type) {
      Print("token 'else' parsing via");
      hold_token = get_token(); // skip else keyword
      parse_stmt_list();
      hold_token = tokens[p_token];

      // missing fi keyword
      if(TK_FI != hold_token.type){
        handle_missing(ERROR_x07,hold_token.row,hold_token.col);
        hold_token = get_token();
        putback(tokens[p_token]);
      }

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

   // missing then keyword
  if(TK_DO != hold_token.type){
    handle_missing(ERROR_x06,hold_token.row,hold_token.col);
    hold_token = get_token();
    putback(tokens[p_token]);
  }

  if (TK_DO == hold_token.type) {
    Print("token 'do' parsing via");
    hold_token = get_token(); // skip do keyword
    parse_stmt_list();
    hold_token = tokens[p_token];

     // missing then keyword
    if(TK_OD != hold_token.type){
      handle_missing(ERROR_x05,hold_token.row,hold_token.col);
      hold_token = get_token();
      putback(tokens[p_token]);
    }

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

  // missing semi colon
  if(TK_READ == hold_token.type || TK_WHILE == hold_token.type 
  || TK_WRITE == hold_token.type || TK_IF == hold_token.type 
  || TK_SKIP == hold_token.type || TK_IDENTIFIER == hold_token.type){
    handle_missing(ERROR_x00,tokens[p_token-1].row,tokens[p_token-1].col);
    hold_token = get_token();
    putback(tokens[p_token]);
  }

  if (TK_SEMI == hold_token.type) {
    match(hold_token, TK_SEMI);
    hold_token = get_token(); // skip ;
    parse_stmt_list();
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
  parse_vardeclation();
  hold_token = get_token();

  if(TK_EOF == hold_token.type){
    return;
  }

  // missing semi colon
  if(TK_READ == hold_token.type || TK_WHILE == hold_token.type 
  || TK_WRITE == hold_token.type || TK_IF == hold_token.type 
  || TK_SKIP == hold_token.type || TK_IDENTIFIER == hold_token.type){
    handle_missing(ERROR_x00,tokens[p_token-1].row,tokens[p_token-1].col);
    hold_token = get_token();
    putback(tokens[p_token - 1]);
  }

  if (TK_SEMI == hold_token.type) {
    match(hold_token, TK_SEMI);
    parse_stmt_list();
  } else {
    return;
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