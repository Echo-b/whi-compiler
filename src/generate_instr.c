#ifndef _GENERATE_INSTR_
#define _GENERATE_INSTR_

#include "defs.h"
#include "error.c"
#include "sys.c"
#include "backpatchlist.h"

void generate_instr_lit(int a) {
  // char instr[8] = {'\0'};
  // sprintf(instr, "lit", a);
  // fprintf(ssam_out, "%s", instr);
  inst_array[instr_cnt].op = _lit;
  inst_array[instr_cnt].a = a;
  instr_cnt++;
}

void generate_instr_wrt() {
  // fprintf(ssam_out, "%s", "wrt\n");
  inst_array[instr_cnt].op = _wrt;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_equ() {
  // fprintf(ssam_out, "%s", "equ\n");
  inst_array[instr_cnt].op = _equ;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_add() {
  // fprintf(ssam_out, "%s", "add\n");
  inst_array[instr_cnt].op = _add;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_sub() {
  // fprintf(ssam_out, "%s", "sub\n");
  inst_array[instr_cnt].op = _sub;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_mul() {
  // fprintf(ssam_out, "%s", "mul\n");
  inst_array[instr_cnt].op = _mul;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_div() {
  // fprintf(ssam_out, "%s", "div\n");
  inst_array[instr_cnt].op = _div;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_nop() {
  // fprintf(ssam_out, "%s", "nop\n");
  inst_array[instr_cnt].op = _nop;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_lth() {
  // fprintf(ssam_out, "%s", "lth\n");
  inst_array[instr_cnt].op = _lth;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_swp() {
  // fprintf(ssam_out, "%s", "swp\n");
  inst_array[instr_cnt].op = _swp;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_jmp(int a) {
  // char instr[8] = {'\0'};
  // sprintf(instr, "jmp %d\n", a);
  // fprintf(ssam_out, "%s", instr);
  inst_array[instr_cnt].op = _jmp;
  inst_array[instr_cnt].a = a;
  instr_cnt++;
}

void generate_instr_jpc(int a) {
  // char instr[8] = {'\0'};
  // sprintf(instr, "jpc %d\n", a);
  // fprintf(ssam_out, "%s", instr);
  inst_array[instr_cnt].op = _jpc;
  inst_array[instr_cnt].a = a;
  instr_cnt++;
}

void generate_instr_sto(Token_t t) {
  // char instr[8] = {'\0'};
  int ret = serchslot(t.str);
  // if (ret == -1) {
  //   printf("%s undefined\n", t.str);
  //   exit(-1);
  // }
  // sprintf(instr, "sto %d\n", ret);
  // fprintf(ssam_out, "%s", instr);
  inst_array[instr_cnt].op = _sto;
  inst_array[instr_cnt].a = ret;
  instr_cnt++;
}

void generate_instr_lod(Token_t t) {
  // char instr[8] = {'\0'};
  int ret = serchslot(t.str);
  // if (ret == -1) {
  //   printf("%s undefined\n", t.str);
  //   exit(-1);
  // }
  // sprintf(instr, "lod %d\n", ret);
  // fprintf(ssam_out, "%s", instr);
  inst_array[instr_cnt].op = _lod;
  inst_array[instr_cnt].a = ret;
  instr_cnt++;
}

void generate_instr_var(Token_t t) {
  generate_instr_lit(0);
  generate_instr_sto(t);
}

void generate_instr_read(Token_t t) {
  // char instr[8] = {'\0'};
  int ret = serchslot(t.str);
  // if (ret == -1) {
  //   printf("%s undefined\n", t.str);
  //   exit(-1);
  // }
  // sprintf(instr, "red %d\n", ret);
  // fprintf(ssam_out, "%s", instr);
  inst_array[instr_cnt].op = _red;
  inst_array[instr_cnt].a = ret;
  instr_cnt++;
}

void generate_instr_write(Token_t t) {
  generate_instr_lod(t);
  generate_instr_wrt();
}

void generate_instr_int(int capacity) {
  // char instr[8] = {'\0'};
  // sprintf(instr, "int %d\n", capacity);
  // fprintf(ssam_out, "%s", instr);
  inst_array[instr_cnt].op = _int;
  inst_array[instr_cnt].a = capacity;
  instr_cnt++;
}


#endif