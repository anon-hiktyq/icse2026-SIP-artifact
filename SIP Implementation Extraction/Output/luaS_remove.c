#include "luaS_remove.h"
void luaS_removeFun(void *p) 
{
    luaS_remove *pIp = (luaS_remove*)p;
  stringtable *tb = &G(pIp -> L)->strt;
  TString **p = &tb->hash[lmod(pIp -> ts->hash, tb->size)];
  while (*p != pIp -> ts)  /* find previous element */
    p = &(*p)->u.hnext;
  *p = (*p)->u.hnext;  /* remove element from its list */
  tb->nuse--;
}