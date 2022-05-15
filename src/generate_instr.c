#ifndef _GENERATE_INSTR_
#define _GENERATE_INSTR_

#include "defs.h"
#include "error.c"
#include "sys.c"

void generate_instr_lit(int a) {
  char instr[8] = {'\0'};
  sprintf(instr, "lit %d\n", a);
  fprintf(ssam_out, "%s", instr);
}

void generate_instr_wrt() {
  fprintf(ssam_out, "%s", "wrt\n");
}

void generate_instr_add() {
  fprintf(ssam_out, "%s", "add\n");
}

void generate_instr_sub() {
  fprintf(ssam_out, "%s", "sub\n");
}

void generate_instr_mul() {
  fprintf(ssam_out, "%s", "mul\n");
}

void generate_instr_div() {
  fprintf(ssam_out, "%s", "div\n");
}

void generate_instr_nop() {
  fprintf(ssam_out, "%s", "nop\n");
}

void generate_instr_lth() {
  fprintf(ssam_out, "%s", "lth\n");
}

void generate_instr_swp() {
  fprintf(ssam_out, "%s", "swp\n");
}

void generate_instr_jmp(int a) {
  char instr[8] = {'\0'};
  sprintf(instr, "jmp %d\n", a);
  fprintf(ssam_out, "%s", instr);
}

void generate_instr_jpc(int a) {
  char instr[8] = {'\0'};
  sprintf(instr, "jpc %d\n", a);
  fprintf(ssam_out, "%s", instr);
}

void generate_instr_sto(Token_t t) {
  char instr[8] = {'\0'};
  int ret = serchslot(t.str);
  if (ret == -1) {
    printf("%s undefined\n", t.str);
    exit(-1);
  }
  sprintf(instr, "sto %d\n", ret);
  fprintf(ssam_out, "%s", instr);
}

void generate_instr_lod(Token_t t) {
  char instr[8] = {'\0'};
  int ret = serchslot(t.str);
  if (ret == -1) {
    printf("%s undefined\n", t.str);
    exit(-1);
  }
  sprintf(instr, "lod %d\n", ret);
  fprintf(ssam_out, "%s", instr);
}

void generate_instr_var(Token_t t) {
  generate_instr_lit(0);
  generate_instr_sto(t);
}

void generate_instr_read(Token_t t) {
  char instr[8] = {'\0'};
  int ret = serchslot(t.str);
  if (ret == -1) {
    printf("%s undefined\n", t.str);
    exit(-1);
  }
  sprintf(instr, "red %d\n", ret);
  fprintf(ssam_out, "%s", instr);
}

void generate_instr_write(Token_t t) {
  generate_instr_lod(t);
  generate_instr_wrt();
}

void generate_instr_int(int capacity) {
  char instr[8] = {'\0'};
  sprintf(instr, "int %d\n", capacity);
  fprintf(ssam_out, "%s", instr);
}

void generate_instr_assg(Token_t t1, Token_t t2) {
  generate_instr_lod(t1);
  generate_instr_sto(t2);
}



#endif