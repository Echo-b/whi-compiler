#ifndef _DEFSH_
#define _DEFSH_

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))

enum {
  TK_NOTYPE = 256,
  TK_EQ,
  TK_IDENTIFIER,  // some custom variable
  TK_NUM,
  TK_PLUS,
  TK_MINUS,
  TK_MUL,
  TK_DIV,
  TK_NOT,
  TK_LESS,
  TK_LP,  // left parenthesis '('
  TK_RP,  // right parenthesis ')'
  TK_SEMI,
  TK_ASSIGN,
  TK_COMMA,
  TK_VAR,
  TK_SKIP,
  TK_READ,
  TK_WRITE,
  TK_IF,
  TK_THEN,
  TK_ELSE,
  TK_FI,
  TK_WHILE,
  TK_DO,
  TK_OD,
  TK_EOF,
  /* TODO: Add more token types */

};

struct rule {
  const char* regex;
  int token_type;
  int precedence;
} rules[] = {

    {"\\s", TK_NOTYPE, 10},                  // spaces
    {"[a-z]+[0-9a-z]*", TK_IDENTIFIER, 10},  // variable definte
    {"=", TK_EQ, 2},                         // equal
    {":=", TK_ASSIGN, 2},
    {",", TK_COMMA, 10},
    {"\\(", TK_LP, 10},      // left parenthesis
    {"\\)", TK_RP, 10},      // right parenthesis
    {"\\+", TK_PLUS, 4},     // plus
    {"-", TK_MINUS, 4},      // minus
    {"\\*", TK_MUL, 5},      // multiple
    {"/", TK_DIV, 5},        // div
    {"[0-9]+", TK_NUM, 10},  // number
    {"~", TK_NOT, 6},        // not
    {"<", TK_LESS, 3},
    {";", TK_SEMI, 10},

};

#define NR_REGEX ARRLEN(rules)

typedef struct token {
  int type;
  char str[32];
  int precedence;
  int row;
  int col;
} Token_t;

struct symtable {
  char* name;
};

#define NGSYSNUM 128
struct symtable Gsyt[NGSYSNUM];
static int Gsyspos = 0;

static Token_t tokens[1024] = {};
static int nr_token = 0;

static int parse_index = 0;

char* keyword_table[] = {"var", "skip", "read", "write", "if", "then", "else", "fi", "while", "do", "od"};

char errinfo[128] = {'0'};

static Token_t put_token = {-1, " ", -1};

static FILE* ssam_out;

static int add_gsyt_flag = 0;

static int row = 1;

#endif