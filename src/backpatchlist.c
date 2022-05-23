#include "backpatchlist.h"
#include "color.h"

/**
 * @brief 
 * 
 * @param next_inst_cnt 
 * @return struct backpatchlist* 
 */
struct backpatchlist *makelist(int next_inst_cnt){
  struct backpatchlist *l = (struct backpatchlist *)malloc(sizeof(struct backpatchlist));
  if(!l){
    printf(RED"memory is full! malloc failed!\n"NONE);
    return nullptr;
  } 
  l->inst_remain = next_inst_cnt;
  l->next = nullptr;
  l->tail = l;
  return l;
}

/**
 * @brief 
 * 
 * @param l1 
 * @param l2 
 * @return struct backpatchlist* 
 */
struct backpatchlist *merge(struct backpatchlist *l1, struct backpatchlist *l2){
  l1->tail = l2;
  return l1;
}

/**
 * @brief 
 * 
 * @param l 
 * @return true 
 * @return false 
 */
bool listfree(struct backpatchlist *l){
  if(!l){
    printf(GREEN"list is null! free successful\n"NONE);
    return true;
  }
  l->inst_remain = 0;
  l->next = nullptr;
  l->tail = nullptr;
  printf(GREEN"list is free successful\n"NONE);
  return true;
}
