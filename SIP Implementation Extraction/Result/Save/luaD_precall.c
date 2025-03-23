#include "luaD_precall.h"
void luaD_precallFun(void *p) 
{
    luaD_precall *pIp = (luaD_precall*)p;
  unsigned status;{status = cast_uint(pIp->nresults + 1);}
  {lua_assert(status <= MAXRESULTS + 1);}
 retry:
  {switch (ttypetag(s2v(pIp->func))) {
    case LUA_VCCL:  /* C closure */
      {precallC(pIp->L, pIp->func, status, clCvalue(s2v(pIp->func))->f);}
      pIp->ret =  NULL;
    case LUA_VLCF:  /* light C function */
      {precallC(pIp->L, pIp->func, status, fvalue(s2v(pIp->func)));}
      pIp->ret =  NULL;
    case LUA_VLCL: {  /* Lua function */
      CallInfo *ci;
      Proto p;{p = clLvalue(s2v(pIp->func))->p;}
      int narg;{narg = cast_int(pIp->L->top.p - pIp->func) - 1;}  /* number of real arguments */
      int nfixparams = p->numparams;
      int fsize = p->maxstacksize;  /* frame size */
      {checkstackp(pIp->L, fsize, pIp->func);}
      {CallInfo * prepCallInfo_ret_0;IPCALL(prepCallInfo,ipprepCallInfo_0,.L = pIp->L,.func = pIp->func,.status = status,.top = func + 1 + fsize,.ret = prepCallInfo_ret_0);pIp->L->ci = ci = prepCallInfo_ret_0;}
      ci->u.l.savedpc = p->code;  /* starting point */
      for (; narg < nfixparams; narg++)
        {setnilvalue(s2v(pIp->L->top.p++));}  /* complete missing arguments */
      {lua_assert(ci->top.p <= pIp->L->stack_last.p);}
      pIp->ret =  ci;
    }
    default: {  /* not a function */
      {checkstackp(pIp->L, 1, pIp->func);}  /* space for metamethod */
      {unsigned int tryfuncTM_ret_0;IPCALL(tryfuncTM,iptryfuncTM_0,.L = pIp->L,.func = pIp->func,.status = status,.ret = &tryfuncTM_ret_0);status = tryfuncTM_ret_0;}  /* try '__call' metamethod */
      goto retry;  /* try again with metamethod */
    }
  }}
}