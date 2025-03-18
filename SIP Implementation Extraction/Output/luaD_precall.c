#include "luaD_precall.h"
void luaD_precallFun(void *p) 
{
    luaD_precall *pIp = (luaD_precall*)p;
  unsigned status = cast_uint(pIp -> nresults + 1);
  lua_assert(status <= MAXRESULTS + 1);
 retry:
  switch (ttypetag(s2v(pIp -> func))) {
    case LUA_VCCL:  /* C closure */
      {int precallC_ret_3;IPCALL(precallC,ipprecallC_1,.pIp->L = pIp->pIp->L,.pIp->func = pIp->pIp->func,.status = status,.f = clCvalue(s2v(pIp->func))->f,.pIp->ret = pIp->&precallC_ret_3);}
      pIp -> ret = NULL;
    case LUA_VLCF:  /* light C function */
      {int precallC_ret_2;IPCALL(precallC,ipprecallC_0,.pIp->L = pIp->pIp->L,.pIp->func = pIp->pIp->func,.status = status,.f = fvalue(s2v(pIp->func)),.pIp->ret = pIp->&precallC_ret_2);}
      pIp -> ret = NULL;
    case LUA_VLCL: {  /* Lua function */
      CallInfo *ci;
      Proto *p = clLvalue(s2v(pIp -> func))->p;
      int narg = cast_int(pIp -> L->top.p - pIp -> func) - 1;  /* number of real arguments */
      int nfixparams = p->numparams;
      int fsize = p->maxstacksize;  /* frame size */
      checkstackp(pIp -> L, fsize, pIp -> func);
      {CallInfo * prepCallInfo_ret_1;IPCALL(prepCallInfo,ipprepCallInfo_0,.L = pIp->L,.func = pIp->func,.status = status,.top = func + 1 + fsize,.ret = pIp->prepCallInfo_ret_1);pIp->L->ci = ci = prepCallInfo_ret_1;}
      ci->u.l.savedpc = p->code;  /* starting point */
      for (; narg < nfixparams; narg++)
        setnilvalue(s2v(pIp -> L->top.p++));  /* complete missing arguments */
      lua_assert(ci->top.p <= pIp -> L->stack_last.p);
      pIp -> ret = ci;
    }
    default: {  /* not a function */
      checkstackp(pIp -> L, 1, pIp -> func);  /* space for metamethod */
      {unsigned int tryfuncTM_ret_0;IPCALL(tryfuncTM,iptryfuncTM_0,.L = pIp->L,.func = pIp->func,.status = status,.ret = pIp->&tryfuncTM_ret_0);status = tryfuncTM_ret_0;}  /* try '__call' metamethod */
      goto retry;  /* try again with metamethod */
    }
  }
}