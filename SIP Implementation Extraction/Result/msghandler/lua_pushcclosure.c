#include "lua_pushcclosure.h"
void lua_pushcclosureFun(void *p) 
{
    lua_pushcclosure *pIp = (lua_pushcclosure*)p;
  {lua_lock(pIp->L);}
  if ((pIp->n) == 0) {
    {setfvalue(s2v(pIp->L->top.p), pIp->fn);}
    {api_incr_top(pIp->L);}
  }
  else {
    int i;
    CClosure *cl;
    {api_checkpop(pIp->L, pIp->n);}
    {api_check(pIp->L, pIp->n <= MAXUPVAL, "upvalue index too large");}
    {CClosure * luaF_newCclosure_ret_0;IPCALL(luaF_newCclosure,ipluaF_newCclosure_0,.ret = luaF_newCclosure_ret_0);cl = luaF_newCclosure_ret_0;}
    cl->f = (pIp->fn);
    for (i = 0; i < (pIp->n); i++) {
      {setobj2n(pIp->L, &cl->upvalue[i], s2v(pIp->L->top.p - pIp->n + i));}
      /* does not need barrier because closure is white */
      {lua_assert(iswhite(cl));}
    }
    (pIp->L)->top.p -= (pIp->n);
    {setclCvalue(pIp->L, s2v(pIp->L->top.p), cl);}
    {api_incr_top(pIp->L);}
    {luaC_checkGC(pIp->L);}
  }
  {lua_unlock(pIp->L);}
}