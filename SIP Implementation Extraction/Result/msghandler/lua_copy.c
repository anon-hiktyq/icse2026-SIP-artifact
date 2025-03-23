#include "lua_copy.h"
void lua_copyFun(void *p) 
{
    lua_copy *pIp = (lua_copy*)p;
  TValue *fr, *to;
  {lua_lock(pIp->L);}
  {TValue * index2value_ret_0;IPCALL(index2value,ipindex2value_0,.L = pIp->L,.idx = pIp->fromidx,.ret = index2value_ret_0);fr = index2value_ret_0;}
  {TValue * index2value_ret_1;IPCALL(index2value,ipindex2value_1,.L = pIp->L,.idx = pIp->toidx,.ret = index2value_ret_1);to = index2value_ret_1;}
  {api_check(pIp->L, isvalid(pIp->L, to), "invalid index");}
  {setobj(pIp->L, to, fr);}
  {if (isupvalue(pIp->toidx))  /* function upvalue? */
    {luaC_barrier(pIp->L, clCvalue(s2v(pIp->L->ci->func.p)), fr);}}
  /* LUA_REGISTRYINDEX does not need gc barrier
     (collector revisits it before finishing collection) */
  {lua_unlock(pIp->L);}
}