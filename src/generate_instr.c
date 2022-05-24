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
  inst_array[instr_cnt].op = lit;
  inst_array[instr_cnt].a = a;
  instr_cnt++;
}

void generate_instr_wrt() {
  // fprintf(ssam_out, "%s", "wrt\n");
  inst_array[instr_cnt].op = wrt;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_equ() {
  // fprintf(ssam_out, "%s", "equ\n");
  inst_array[instr_cnt].op = equ;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_add() {
  // fprintf(ssam_out, "%s", "add\n");
  inst_array[instr_cnt].op = add;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_sub() {
  // fprintf(ssam_out, "%s", "sub\n");
  inst_array[instr_cnt].op = sub;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_mul() {
  // fprintf(ssam_out, "%s", "mul\n");
  inst_array[instr_cnt].op = mul;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_div() {
  // fprintf(ssam_out, "%s", "div\n");
  inst_array[instr_cnt].op = div;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_nop() {
  // fprintf(ssam_out, "%s", "nop\n");
  inst_array[instr_cnt].op = nop;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_lth() {
  // fprintf(ssam_out, "%s", "lth\n");
  inst_array[instr_cnt].op = lth;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_swp() {
  // fprintf(ssam_out, "%s", "swp\n");
  inst_array[instr_cnt].op = swp;
  inst_array[instr_cnt].a = null;
  instr_cnt++;
}

void generate_instr_jmp(int a) {
  // char instr[8] = {'\0'};
  // sprintf(instr, "jmp %d\n", a);
  // fprintf(ssam_out, "%s", instr);
  inst_array[instr_cnt].op = jmp;
  inst_array[instr_cnt].a = a;
  instr_cnt++;
}

void generate_instr_jpc(int a) {
  // char instr[8] = {'\0'};
  // sprintf(instr, "jpc %d\n", a);
  // fprintf(ssam_out, "%s", instr);
  inst_array[instr_cnt].op = jpc;
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
  inst_array[instr_cnt].op = sto;
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
  inst_array[instr_cnt].op = lod;
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
  inst_array[instr_cnt].op = red;
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
  inst_array[instr_cnt].op = Int;
  inst_array[instr_cnt].a = capacity;
  instr_cnt++;
}


#endif