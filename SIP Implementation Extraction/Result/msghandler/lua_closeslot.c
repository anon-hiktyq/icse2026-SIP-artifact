#include "lua_closeslot.h"
void lua_closeslotFun(void *p) 
{
    lua_closeslot *pIp = (lua_closeslot*)p;
  StkId level;
  {lua_lock(pIp->L);}
  {StkId index2stack_ret_0;IPCALL(index2stack,ipindex2stack_0,.L = pIp->L,.idx = pIp->idx,.ret = &index2stack_ret_0);level = index2stack_ret_0;}
  {api_check(pIp->L, (pIp->L->ci->callstatus & CIST_TBC) && (pIp->L->tbclist.p == level),
     "no variable to close at given level");}
  {StkId luaF_close_ret_0;IPCALL(luaF_close,ipluaF_close_0,.ret = &luaF_close_ret_0);level = luaF_close_ret_0;}
  {setnilvalue(s2v(level));}
  {lua_unlock(pIp->L);}
}