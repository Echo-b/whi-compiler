#ifndef _GENERATE_INSTR_
#define _GENERATE_INSTR_

#include "defs.h"
#include "error.c"
#include "sys.c"

void generate_instr_lit() {
  fprintf(ssam_out, "%s", "lit 0\n");
}

void generate_instr_wrt() {
  fprintf(ssam_out, "%s", "wrt\n");
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
  generate_instr_lit();
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

void generate_instr_nop() {
  fprintf(ssam_out, "%s", "nop\n");
}

void generate_instr_write(Token_t t) {
  generate_instr_lod(t);
  generate_instr_wrt();
}

void generate_instr_int() {
  char instr[8] = {'\0'};
  sprintf(instr, "int %d\n", Gsyspos);
  fprintf(ssam_out, "%s", instr);
}

void generate_instr_assg(Token_t t1, Token_t t2) {
  generate_instr_lod(t1);
  generate_instr_sto(t2);
}

#endif