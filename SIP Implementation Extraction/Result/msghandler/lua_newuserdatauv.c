#include "lua_newuserdatauv.h"
void lua_newuserdatauvFun(void *p) 
{
    lua_newuserdatauv *pIp = (lua_newuserdatauv*)p;
  Udata *u;
  {lua_lock(pIp->L);}
  {api_check(pIp->L, 0 <= pIp->nuvalue && pIp->nuvalue < SHRT_MAX, "invalid value");}
  {u = luaS_newudata(pIp->L, pIp->size, cast(unsigned short, pIp->nuvalue));}
  {setuvalue(pIp->L, s2v(pIp->L->top.p), u);}
  {api_incr_top(pIp->L);}
  {luaC_checkGC(pIp->L);}
  {lua_unlock(pIp->L);}
  pIp->ret =  getudatamem(u);
}