#include "freehash.h"
void freehashFun(void *p) 
{
    freehash *pIp = (freehash*)p;
  if (!isdummy(pIp -> t)) {
    /* get pointer to the beginning of Node array */
    char *arr = cast_charp(pIp -> t->node) - extraLastfree(pIp -> t);
    luaM_freearray(pIp -> L, arr, sizehash(pIp -> t));
  }
}