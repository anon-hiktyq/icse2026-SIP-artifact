#include "freeupval.h"
void freeupvalFun(void *p) 
{
    freeupval *pIp = (freeupval*)p;
  {if (upisopen(pIp->uv))
    {IPCALL(luaF_unlinkupval,ipluaF_unlinkupval_0);}}
  {luaM_free(pIp->L, pIp->uv);}
}