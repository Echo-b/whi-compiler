#ifndef _PATCH_LIST
#define _PATCH_LIST
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct backpatchlist
{
  int inst_remain;
  struct backpatchlist *tail;
  struct backpatchlist *next;
};

#define nullptr NULL

//instruction data structure definition
enum func_code {
  add,
  sub,
  mul,
  div,
  equ,
  lth,
  lit,
  sto,
  lod,
  Int,
  jmp,
  jpc,
  red,
  wrt,
  swp,
  nop,
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
struct backpatchlist *merge(struct backpatchlist *l1, struct backpatchlist *l2);
bool listfree(struct backpatchlist *l);

#endif