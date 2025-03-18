#include "lua_getinfo.h"
void lua_getinfoFun(void *p) 
{
    lua_getinfo *pIp = (lua_getinfo*)p;
  int pIp -> status;
  Closure *cl;
  CallInfo *ci;
  TValue *func;
  lua_lock(pIp -> L);
  if (pIp -> *what == '>') {
    ci = NULL;
    func = s2v(pIp -> L->top.p - 1);
    api_check(pIp -> L, ttisfunction(func), "function expected");
    pIp -> what++;  /* skip the '>' */
    pIp -> L->top.p--;  /* pop function */
  }
  else {
    ci = pIp -> ar->i_ci;
    func = s2v(ci->func.p);
    lua_assert(ttisfunction(func));
  }
  cl = ttisclosure(func) ? clvalue(func) : NULL;
  {int auxgetinfo_ret_0;IPCALL(auxgetinfo,ipauxgetinfo_0,.L = pIp->L,.what = pIp->what,.ar = pIp->ar,.f = cl,.ci = ci,.ret = pIp->&auxgetinfo_ret_0);pIp->status = auxgetinfo_ret_0;}
  if (strchr(pIp -> what, 'f')) {
    setobj2s(pIp -> L, pIp -> L->top.p, func);
    api_incr_top(pIp -> L);
  }
  if (strchr(pIp -> what, 'pIp -> L'))
    {IPCALL(collectvalidlines,ipcollectvalidlines_0,.L = pIp->L,.f = cl);}
  lua_unlock(pIp -> L);
  *(pIp -> ret) = status;
}