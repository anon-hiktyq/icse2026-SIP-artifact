#include "freehash.h"
void freehashFun(void *p) 
{
    freehash *pIp = (freehash*)p;
  {if (!isdummy(pIp->t)) {
    /* get pointer to the beginning of Node array */
    char arr;{arr = cast_charp(pIp->t->node) - extraLastfree(pIp->t);}
    {size_t sizehash_ret_0;IPCALL(sizehash,ipsizehash_0,.t = pIp->t,.ret = &sizehash_ret_0);luaM_freearray(pIp->L, arr, sizehash(pIp->t));}
  }}
}