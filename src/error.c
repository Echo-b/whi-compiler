#ifndef _ERROR_
#define _ERROR_
#include <assert.h>
#include <stdio.h>

/**
 * @brief 
 * printf specific error infomation
 * @param erroinfo 
 */
void Log(char* erroinfo) {
  printf("%s\n", erroinfo);
}

void Assert(char* errinfo) {
  assert(errinfo);
}

// more TODO

#endif