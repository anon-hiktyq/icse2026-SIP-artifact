#include "precallC.h"
void precallCFun(void *p) 
{
    precallC *pIp = (precallC*)p;

  int n;  /* number of returns */
  CallInfo *ci;
  checkstackp(pIp -> L, LUA_MINSTACK, pIp -> func);  /* ensure minimum stack size */
  {CallInfo * prepCallInfo_ret_0;IPCALL(prepCallInfo,ipprepCallInfo_0,.L = pIp->L,.func = pIp->func,.status = pIp->status | CIST_C,.top = L->top.p + LUA_MINSTACK,.ret = pIp->prepCallInfo_ret_0);pIp->L->ci = ci = prepCallInfo_ret_0;}

  lua_assert(ci->top.p <= pIp -> L->stack_last.p);
  if (l_unlikely(pIp -> L->hookmask & LUA_MASKCALL)) {
    int narg = cast_int(pIp -> L->top.p - pIp -> func) - 1;
    {IPCALL(luaD_hook,ipluaD_hook_0,.L = pIp->L,.event = LUA_HOOKCALL,.line = -1,.ftransfer = 1,.ntransfer = narg);}
  }
  lua_unlock(pIp -> L);
  n = (pIp -> *f)(pIp -> L);  /* do the actual call */
  lua_lock(pIp -> L);
  api_checknelems(pIp -> L, n);
  {IPCALL(luaD_poscall,ipluaD_poscall_0,.L = pIp->L,.ci = ci,.nres = n);}
  *(pIp -> ret) = n;
}