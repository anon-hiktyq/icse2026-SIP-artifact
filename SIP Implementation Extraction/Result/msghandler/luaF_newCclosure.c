#include "luaF_newCclosure.h"
void luaF_newCclosureFun(void *p) 
{
    luaF_newCclosure *pIp = (luaF_newCclosure*)p;
  GCObject o;{o = luaC_newobj(pIp->L, LUA_VCCL, sizeCclosure(pIp->nupvals));}
  CClosure c;{c = gco2ccl(o);}
  {c->nupvalues = cast_byte(pIp->nupvals);}
  pIp->ret =  c;
}