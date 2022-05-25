#ifndef _PATCH_LIST
#define _PATCH_LIST
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "color.h"

struct backpatchlist
{
  int inst_remain;
  struct backpatchlist *tail;
  struct backpatchlist *next;
};

#define nullptr NULL

//instruction data structure definition
enum func_code {
  _add,
  _sub,
  _mul,
  _div,
  _equ,
  _lth,
  _lit,
  _sto,
  _lod,
  _int,
  _jmp,
  _jpc,
  _red,
  _wrt,
  _swp,
  _nop,
};

struct instruction {
  enum func_code op;
  int a;
};

#define null -1

static int instr_cnt = 0;
#define instr_array_num  512
struct instruction inst_array[instr_array_num];


// helper function definition
static int nextinst(){
  return instr_cnt;
}

struct backpatchlist *makelist(int next_inst_cnt);
struct backpatchlist *merge(struct backpatchlist *bpl1, struct backpatchlist *bpl2);
bool backpatch(struct backpatchlist *bpl, int next_inst_cnt);
int length(struct backpatchlist *bpl);
struct  backpatchlist *brf();
struct  backpatchlist *br();
struct  backpatchlist *endif(struct backpatchlist *lb ,struct backpatchlist *lst1 ,struct backpatchlist *lst2);
bool listfree(struct backpatchlist *bpl);
void printbpl(struct backpatchlist *bpl);
bool out_ssam_code(FILE* fd);

#endif