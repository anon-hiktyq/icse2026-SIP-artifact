#include "luaF_freeproto.h"
void luaF_freeprotoFun(void *p) 
{
    luaF_freeproto *pIp = (luaF_freeproto*)p;
  if (!((pIp->f)->flag & PF_FIXED)) {
    {luaM_freearray(pIp->L, pIp->f->code, cast_sizet(pIp->f->sizecode));}
    {luaM_freearray(pIp->L, pIp->f->lineinfo, cast_sizet(pIp->f->sizelineinfo));}
    {luaM_freearray(pIp->L, pIp->f->abslineinfo, cast_sizet(pIp->f->sizeabslineinfo));}
  }
  {luaM_freearray(pIp->L, pIp->f->p, cast_sizet(pIp->f->sizep));}
  {luaM_freearray(pIp->L, pIp->f->k, cast_sizet(pIp->f->sizek));}
  {luaM_freearray(pIp->L, pIp->f->locvars, cast_sizet(pIp->f->sizelocvars));}
  {luaM_freearray(pIp->L, pIp->f->upvalues, cast_sizet(pIp->f->sizeupvalues));}
  {luaM_free(pIp->L, pIp->f);}
}