#include "luaD_pretailcall.h"
void luaD_pretailcallFun(void *p) 
{
    luaD_pretailcall *pIp = (luaD_pretailcall*)p;
  unsigned status = LUA_MULTRET + 1;
 retry:
  {switch (ttypetag(s2v(pIp->func))) {
    case LUA_VCCL:  /* C closure */
      *(pIp->ret) =  precallC(L, func, status, clCvalue(s2v(func))->f);
    case LUA_VLCF:  /* light C function */
      *(pIp->ret) =  precallC(L, func, status, fvalue(s2v(func)));
    case LUA_VLCL: {  /* Lua function */
      Proto p;{p = clLvalue(s2v(pIp->func))->p;}
      int fsize = p->maxstacksize;  /* frame size */
      int nfixparams = p->numparams;
      int i;
      {checkstackp(pIp->L, fsize - pIp->delta, pIp->func);}
      (pIp->ci)->func.p -= (pIp->delta);  /* restore 'func' (if vararg) */
      for (i = 0; i < (pIp->narg1); i++)  /* move down function and arguments */
        {setobjs2s(pIp->L, pIp->ci->pIp->func.p + i, pIp->func + i);}
      (pIp->func) = (pIp->ci)->func.p;  /* moved-down function */
      for (; (pIp->narg1) <= nfixparams; (pIp->narg1)++)
        {setnilvalue(s2v(pIp->func + pIp->narg1));}  /* complete missing arguments */
      (pIp->ci)->top.p = (pIp->func) + 1 + fsize;  /* top for new function */
      {lua_assert(pIp->ci->top.p <= pIp->L->stack_last.p);}
      (pIp->ci)->u.l.savedpc = p->code;  /* starting point */
      (pIp->ci)->callstatus |= CIST_TAIL;
      (pIp->L)->top.p = (pIp->func) + (pIp->narg1);  /* set top */
      *(pIp->ret) =  -1;
    }
    default: {  /* not a function */
      {checkstackp(pIp->L, 1, pIp->func);}  /* space for metamethod */
      {unsigned int tryfuncTM_ret_0;IPCALL(tryfuncTM,iptryfuncTM_0,.L = pIp->L,.func = pIp->func,.status = status,.ret = &tryfuncTM_ret_0);status = tryfuncTM_ret_0;}  /* try '__call' metamethod */
      (pIp->narg1)++;
      goto retry;  /* try again */
    }
  }}
}