#include "lua_pushvalue.h"
void lua_pushvalueFun(void *p) 
{
    lua_pushvalue *pIp = (lua_pushvalue*)p;
  {lua_lock(pIp->L);}
  {TValue * index2value_ret_0;IPCALL(index2value,ipindex2value_0,.L = pIp->L,.idx = pIp->idx,.ret = index2value_ret_0);setobj2s(pIp->L, pIp->L->top.p, index2value(pIp->L, pIp->idx));}
  {api_incr_top(pIp->L);}
  {lua_unlock(pIp->L);}
}