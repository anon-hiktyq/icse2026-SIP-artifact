#include "luaF_close.h"
void luaF_closeFun(void *p) 
{
    luaF_close *pIp = (luaF_close*)p;
  ptrdiff_t levelrel = savestack(pIp -> L, pIp -> level);
  {IPCALL(luaF_closeupval,ipluaF_closeupval_0,.L = pIp->L,.level = pIp->level);}  /* first, close the upvalues */
  while (pIp -> L->tbclist.p >= pIp -> level) {  /* traverse tbc's down to that pIp -> level */
    StkId tbc = pIp -> L->tbclist.p;  /* get variable index */
    {IPCALL(poptbclist,ippoptbclist_0,.L = pIp->L);}  /* remove it from list */
    {IPCALL(prepcallclosemth,ipprepcallclosemth_0,.L = pIp->L,.level = pIp->tbc,.status = pIp->status,.yy = pIp->yy);}  /* close variable */
    pIp -> level = restorestack(pIp -> L, levelrel);
  }
  *(pIp -> ret) = level;
}