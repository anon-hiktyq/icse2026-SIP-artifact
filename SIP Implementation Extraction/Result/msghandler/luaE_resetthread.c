#include "luaE_resetthread.h"
void luaE_resetthreadFun(void *p) 
{
    luaE_resetthread *pIp = (luaE_resetthread*)p;
  CallInfo *ci = pIp -> L->ci = pIp -> &L->base_ci;  /* unwind CallInfo list */
  setnilvalue(s2v(pIp -> L->stack.p));  /* 'function' entry for basic 'ci' */
  ci->func.p = pIp -> L->stack.p;
  ci->callstatus = CIST_C;
  if (pIp -> status == LUA_YIELD)
    pIp -> status = LUA_OK;
  pIp -> L->pIp -> status = LUA_OK;  /* so it can run __close metamethods */
  {TStatus luaD_closeprotected_ret_1;IPCALL(luaD_closeprotected,ipluaD_closeprotected_0,.ret = pIp->&luaD_closeprotected_ret_1);pIp->status = luaD_closeprotected_ret_1;}
  if (pIp -> status != LUA_OK)  /* errors? */
    luaD_seterrorobj(pIp -> L, pIp -> status, pIp -> L->stack.p + 1);
  else
    pIp -> L->top.p = pIp -> L->stack.p + 1;
  ci->top.p = pIp -> L->top.p + LUA_MINSTACK;
  {int luaD_reallocstack_ret_0;IPCALL(luaD_reallocstack,ipluaD_reallocstack_0,.ret = pIp->&luaD_reallocstack_ret_0);}
  *(pIp -> ret) = status;
}