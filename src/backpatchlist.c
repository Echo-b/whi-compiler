#include "backpatchlist.h"
#include "color.h"

/**
 * @brief 
 * 
 * @param next_inst_cnt 
 * @return struct backpatchlist* 
 */
struct backpatchlist *makelist(int next_inst_cnt){
  struct backpatchlist *bpl = (struct backpatchlist *)malloc(sizeof(struct backpatchlist));
  if(!bpl){
    printf(RED"memory is full! malloc failed!\n"NONE);
    return nullptr;
  } 
  bpl->inst_remain = next_inst_cnt;
  bpl->next = nullptr;
  bpl->tail = bpl;
  return bpl;
}

/**
 * @brief 
 * 
 * @param bpl1 
 * @param bpl2 
 * @return struct backpatchlist* 
 */
struct backpatchlist *merge(struct backpatchlist *bpl1, struct backpatchlist *bpl2){
  bpl1->tail = bpl2;
  return bpl1;
}

/**
 * @brief 
 * 
 * @param bpl 
 * @param next_inst_cnt 
 * @return true 
 * @return false 
 */
bool backpatch(struct backpatchlist *bpl, int next_inst_cnt){
  if(!bpl){
    printf(RED"back patch list is null!\n"NONE);
    return false;
  }
  struct backpatchlist *tmp = bpl;
  while(tmp){
    inst_array[tmp->inst_remain].a = next_inst_cnt;
    tmp = tmp->next;
  }
  printf(GREEN"call backpatch function successful!\n"NONE);
  return true;

}

/**
 * @brief 
 * 
 * @param bpl 
 * @return int 
 */
int length(struct backpatchlist *bpl){
  struct backpatchlist *tmp = bpl;
  if(!tmp){
    return 0;
  }
  int len = 0;
  while(tmp){
    ++len;
    tmp = tmp->next;
  }
  return len;
}

/**
 * @brief 
 * 
 * @param bpl 
 * @return true 
 * @return false 
 */
bool listfree(struct backpatchlist *bpl){
  if(!bpl){
    printf(GREEN"list is null! free successful\n"NONE);
    return true;
  }
  bpl->inst_remain = 0;
  bpl->next = nullptr;
  bpl->tail = nullptr;
  printf(GREEN"list is free successful\n"NONE);
  return true;
}
