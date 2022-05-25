#include "backpatchlist.h"

extern void generate_instr_jmp(int a);
extern void generate_instr_jpc(int a);

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
  if(!bpl1 && !bpl2){
    return nullptr;
  } else if(!bpl1 && bpl2){
    return bpl2;
  } else if(bpl1 && !bpl2){
    return bpl1;
  } else{
    bpl1->tail->next = bpl2;
    bpl1->tail = bpl2->tail;
    return bpl1;
  }
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
    printf(GREEN"the bpl is null ,no operate return\n"NONE);
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
  if(!bpl){
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

/**
 * @brief 
 * 
 * @return struct backpatchlist* 
 */
struct  backpatchlist *brf(){
  struct  backpatchlist *la = makelist(nextinst());
  if(!la){
    printf(RED"malloc memory failed!"NONE);
    return  nullptr ;
  }
  generate_instr_jpc(-1);
  return la;
}

/**
 * @brief 
 * 
 * @return struct backpatchlist* 
 */
struct  backpatchlist *br(){
  struct  backpatchlist *lb = makelist(nextinst());
  if(!lb){
    printf(RED"malloc memory failed!"NONE);
    return  nullptr;
  }
  generate_instr_jmp(-1);
  return lb;
}

/**
 * @brief 
 * 
 * @param lb 
 * @param lst1 
 * @param lst2 
 * @return struct backpatchlist* 
 */
struct  backpatchlist *endif(struct backpatchlist *lb ,struct backpatchlist *lst1 ,struct backpatchlist *lst2){
  struct backpatchlist *lst = merge(merge(lst1,lb) ,lst2);
  if(!lst){
    printf(RED"call endif failed!"NONE);
    return  nullptr;
  }
  return lst;
}

/**
 * @brief 
 * 
 * @param bpl 
 */
void printbpl(struct backpatchlist *bpl){
  if(!bpl){
    printf(GREEN"list is null\n"NONE);
    return;
  }
  struct backpatchlist *tmp = bpl;
  while(tmp){
    printf("the instr cnt is %d\n",tmp->inst_remain);
    tmp = tmp->next;
  }
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool out_ssam_code(FILE* fd){
  char instr[8] = {'\0'};
  for(int i = 0; i < instr_cnt; ++i){
    switch (inst_array[i].op)
    {
    case _add:
      sprintf(instr, "add\n");
      break;
    case _sub:
      sprintf(instr, "sub\n");
      break;
    case _mul:
      sprintf(instr, "mul\n");
      break;
    case _div:
      sprintf(instr, "div\n");
      break;
    case _equ:
      sprintf(instr, "equ\n");
      break;
    case _lth:
      sprintf(instr, "lth\n");
      break;
    case _wrt:
      sprintf(instr, "wrt\n");
      break;
    case _swp:
      sprintf(instr, "swp\n");
      break;
    case _nop:
      sprintf(instr, "nop\n");
      break;
    case _lit:
      sprintf(instr, "lit  %d\n" ,inst_array[i].a);
      break;
    case _sto:
      sprintf(instr, "sto  %d\n" ,inst_array[i].a);
      break;
    case _lod:
      sprintf(instr, "lod  %d\n" ,inst_array[i].a);
      break;
    case _int:
      sprintf(instr, "int  %d\n" ,inst_array[i].a);
      break;
    case _jmp:
      sprintf(instr, "jmp  %d\n" ,inst_array[i].a);
      break;
    case _jpc:
      sprintf(instr, "jpc  %d\n" ,inst_array[i].a);
      break;
    case _red:
      sprintf(instr, "red  %d\n" ,inst_array[i].a);
      break;
    default:
      break;
    }
    fprintf(fd, "%s", instr);
  }
  printf(GREEN"[success] generate simple stack machine code successful!\n"NONE);
  return true;
}

