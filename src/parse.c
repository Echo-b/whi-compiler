#ifndef _PARSE_
#define _PARSE_

#include "parse.h"
#include "defs.h"
#include "generate_instr.c"
#include "helper.c"

/**
 * @brief 
 * parse variable definite
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_vardeclation(){

}

/**
 * @brief 
 * parse expression such as if,while and so on
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_expression(){

}

/**
 * @brief 
 * parse skip statement and generate the nop instr
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_skip_stmt(){

}

/**
 * @brief 
 * parse assign statement(x:=y)
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_assg_stmt(){

}

/**
 * @brief 
 * parse  read statement and generate read instr
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_read_stmt(){

}

/**
 * @brief 
 * parse write statement and generate write instr
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_write_stmt(){

}

/**
 * @brief 
 * parse if statement
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_if_stmt(){

}

/**
 * @brief 
 * parse while statement
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_while_stmt(){

}

/**
 * @brief 
 * parse statement 
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_statement(){

}

/**
 * @brief 
 * parse statement list
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_stmt_list(){

}

/**
 * @brief 
 * parse program 
 * nothing on successful
 * call handle_error() function on failure 
 */
void parse_program(){

}

/**
 * @brief 
 * call parse_program() function and match the TK_EOF token
 * return 0 on successful
 * return -1 on failure
 * @return int 
 */
int parse(){

}

#endif