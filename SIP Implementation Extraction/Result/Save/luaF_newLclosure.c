#include "luaF_newLclosure.h"
void luaF_newLclosureFun(void *p) 
{
    luaF_newLclosure *pIp = (luaF_newLclosure*)p;
  GCObject o;{o = luaC_newobj(pIp->L, LUA_VLCL, sizeLclosure(pIp->nupvals));}
  LClosure c;{c = gco2lcl(o);}
  c->p = NULL;
  {c->nupvalues = cast_byte(pIp->nupvals);}
  while ((pIp->nupvals)--) c->upvals[(pIp->nupvals)] = NULL;
  pIp->ret =  c;
}