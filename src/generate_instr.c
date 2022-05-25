#ifndef _GENERATE_INSTR_
#define _GENERATE_INSTR_

#include "defs.h"
#include "error.c"
#include "sys.c"
#include "backpatchlist.h"

void generate_instr_lit(int a) {
  inst_array[instr_cnt].op = _lit;
  inst_array[instr_cnt].a = a;
  instr_cnt++;
}

void generate_instr_wrt() {
  inst_array[instr_cnt].op = _wrt;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_equ() {
  inst_array[instr_cnt].op = _equ;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_add() {
  inst_array[instr_cnt].op = _add;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_sub() {
  inst_array[instr_cnt].op = _sub;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_mul() {
  inst_array[instr_cnt].op = _mul;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_div() {
  inst_array[instr_cnt].op = _div;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_nop() {
  inst_array[instr_cnt].op = _nop;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_lth() {
  inst_array[instr_cnt].op = _lth;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_swp() {
  inst_array[instr_cnt].op = _swp;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_jmp(int a) {
  inst_array[instr_cnt].op = _jmp;
  inst_array[instr_cnt].a = a;
  instr_cnt++;
}

void generate_instr_jpc(int a) {
  inst_array[instr_cnt].op = _jpc;
  inst_array[instr_cnt].a = a;
  instr_cnt++;
}

void generate_instr_sto(Token_t t) {
  int ret = serchslot(t.str);
  inst_array[instr_cnt].op = _sto;
  inst_array[instr_cnt].a = ret;
  instr_cnt++;
}

void generate_instr_lod(Token_t t) {
  int ret = serchslot(t.str);
  inst_array[instr_cnt].op = _lod;
  inst_array[instr_cnt].a = ret;
  instr_cnt++;
}

void generate_instr_var(Token_t t) {
  generate_instr_lit(0);
  generate_instr_sto(t);
}

void generate_instr_read(Token_t t) {
  int ret = serchslot(t.str);
  inst_array[instr_cnt].op = _red;
  inst_array[instr_cnt].a = ret;
  instr_cnt++;
}

void generate_instr_int(int capacity) {
  inst_array[instr_cnt].op = _int;
  inst_array[instr_cnt].a = capacity;
  instr_cnt++;
}

#endif