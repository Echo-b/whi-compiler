#ifndef _SYS_
#define _SYS_
#include "defs.h"
#include "error.c"

/**
 * @brief
 * add a variable into the globle symbol table
 * return specific position on successful
 * return -1 on failure
 * @return int
 */
int addglob(char* identifier) {
  if ((Gsyspos + 1) < NGSYSNUM)
    Gsyt[Gsyspos++].name = identifier;
  else {
    Log("globle symbol table size is not enough!");
    return (-1);
  }
  return Gsyspos;
}

/**
 * @brief
 * search the specific identifier position and return the slot number
 * return slot not equal -1 on successful
 * return -1 on unsuccessful
 * @param identifier
 * @return int
 */
int serchslot(char* identifier) {
  int slot = -1;
  for (int i = 0; i < Gsyspos; ++i) {
    if (!strcmp(Gsyt[i].name, identifier)) {
      slot = i;
      break;
    }
  }
  return slot;
}

/**
 * @brief
 * print the globle symbol table
 */
void show_systable() {
  for (int i = 0; i < Gsyspos; i++)
    printf("the var name is [%s],the position is [%d]\n", Gsyt[i].name, i);
}

#endif