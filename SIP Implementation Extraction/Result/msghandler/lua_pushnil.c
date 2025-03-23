#include "lua_pushnil.h"
void lua_pushnilFun(void *p) 
{
    lua_pushnil *pIp = (lua_pushnil*)p;
  {lua_lock(pIp->L);}
  {setnilvalue(s2v(pIp->L->top.p));}
  {api_incr_top(pIp->L);}
  {lua_unlock(pIp->L);}
}