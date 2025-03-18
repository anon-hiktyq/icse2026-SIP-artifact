#include "tryfuncTM.h"
void tryfuncTMFun(void *p) 
{
    tryfuncTM *pIp = (tryfuncTM*)p;
  const TValue *tm;
  StkId p;
  {const TValue * luaT_gettmbyobj_ret_0;IPCALL(luaT_gettmbyobj,ipluaT_gettmbyobj_0,.ret = pIp->luaT_gettmbyobj_ret_0);tm = luaT_gettmbyobj_ret_0;}
  if (l_unlikely(ttisnil(tm)))  /* no metamethod? */
    {IPCALL(luaG_callerror,ipluaG_callerror_0);}
  for (p = pIp -> L->top.p; p > pIp -> func; p--)  /* open space for metamethod */
    setobjs2s(pIp -> L, p, p-1);
  pIp -> L->top.p++;  /* stack space pre-allocated by the caller */
  setobj2s(pIp -> L, pIp -> func, tm);  /* metamethod is the new function to be called */
  if ((pIp -> status & MAX_CCMT) == MAX_CCMT)  /* is counter full? */
    {IPCALL(luaG_runerror,ipluaG_runerror_0);}
  *(pIp -> ret) = status + (1u << CIST_CCMT); /* increment counter */
}