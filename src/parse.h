#ifndef _PARSE_H_
#define _PARSE_H_
#include "backpatchlist.c"

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
struct backpatchlist *parse_if_stmt();
struct backpatchlist *parse_while_stmt();
struct backpatchlist *parse_statement();
struct backpatchlist *parse_stmt_list();
void parse_program();
int parse(FILE *out);

#endif