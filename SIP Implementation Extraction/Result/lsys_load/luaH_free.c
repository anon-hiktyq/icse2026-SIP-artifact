#include "luaH_free.h"
void luaH_freeFun(void *p) 
{
    luaH_free *pIp = (luaH_free*)p;
  {IPCALL(freehash,ipfreehash_0,.L = pIp->L,.t = pIp->t);}
  {Value * resizearray_ret_0;IPCALL(resizearray,ipresizearray_0,.L = pIp->L,.t = pIp->t,.oldasize = t->asize,.newasize = 0,.ret = resizearray_ret_0);resizearray_ret_0;}
  {luaM_free(pIp->L, pIp->t);}
}