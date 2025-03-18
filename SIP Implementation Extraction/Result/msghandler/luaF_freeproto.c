#include "luaF_freeproto.h"
void luaF_freeprotoFun(void *p) 
{
    luaF_freeproto *pIp = (luaF_freeproto*)p;
  if (!(pIp -> f->flag & PF_FIXED)) {
    luaM_freearray(pIp -> L, pIp -> f->code, cast_sizet(pIp -> f->sizecode));
    {IPCALL(luaM_free_,ipluaM_free__3);}
    luaM_freearray(pIp -> L, pIp -> f->abslineinfo, cast_sizet(pIp -> f->sizeabslineinfo));
  }
  {IPCALL(luaM_free_,ipluaM_free__2);}
  luaM_freearray(pIp -> L, pIp -> f->k, cast_sizet(pIp -> f->sizek));
  {IPCALL(luaM_free_,ipluaM_free__1);}
  luaM_freearray(pIp -> L, pIp -> f->upvalues, cast_sizet(pIp -> f->sizeupvalues));
  {IPCALL(luaM_free_,ipluaM_free__0);}
}