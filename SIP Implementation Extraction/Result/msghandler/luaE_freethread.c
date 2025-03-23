#include "luaE_freethread.h"
void luaE_freethreadFun(void *p) 
{
    luaE_freethread *pIp = (luaE_freethread*)p;
  LX l;{l = fromstate(pIp->L1);}
  {IPCALL(luaF_closeupval,ipluaF_closeupval_0);}  /* close all upvalues */
  {lua_assert(pIp->L1->openupval == NULL);}
  {luai_userstatefree(pIp->L, pIp->L1);}
  {IPCALL(freestack,ipfreestack_0,.L = pIp->L1);}
  {luaM_free(pIp->L, l);}
}