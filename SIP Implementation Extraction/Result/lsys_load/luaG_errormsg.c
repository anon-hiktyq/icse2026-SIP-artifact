#include "luaG_errormsg.h"
void luaG_errormsgFun(void *p) 
{
    luaG_errormsg *pIp = (luaG_errormsg*)p;
  if ((pIp->L)->errfunc != 0) {  /* is there an error handling function? */
    StkId errfunc;{errfunc = restorestack(pIp->L, pIp->L->errfunc);}
    {lua_assert(ttisfunction(s2v(errfunc)));}
    {setobjs2s(pIp->L, pIp->L->top.p, pIp->L->top.p - 1);}  /* move argument */
    {setobjs2s(pIp->L, pIp->L->top.p - 1, errfunc);}  /* push function */
    (pIp->L)->top.p++;  /* assume EXTRA_STACK */
    {IPCALL(luaD_callnoyield,ipluaD_callnoyield_0);}  /* call it */
  }
  {IPCALL(luaD_throw,ipluaD_throw_0);}
}