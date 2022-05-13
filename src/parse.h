#ifndef _PARSE_H_
#define _PARSE_H_

void parse_vardeclation();
void parse_expression();
void parse_subexpression_TS();
void parse_subexpression_T();
void parse_subexpression_FS();
void parse_subexpression_F();
void parse_subexpression_D1();
void parse_subexpression_D();
void pasee_subexpression_N();
void pasee_subexpression_V();
void parse_skip_stmt();
void parse_assg_stmt();
void parse_read_stmt();
void parse_write_stmt();
void parse_if_stmt();
void parse_while_stmt();
void parse_statement();
void parse_stmt_list();
void parse_program();
int parse();

#endif