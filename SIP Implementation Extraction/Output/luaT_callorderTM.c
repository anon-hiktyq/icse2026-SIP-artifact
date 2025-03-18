#include "luaT_callorderTM.h"
void luaT_callorderTMFun(void *p) 
{
    luaT_callorderTM *pIp = (luaT_callorderTM*)p;

  int tag;{int callbinTM_ret_0;IPCALL(callbinTM,ipcallbinTM_0,.L = pIp->L,.p1 = pIp->p1,.p2 = pIp->p2,.res = L->top.p,.event = pIp->event,.ret = pIp->&callbinTM_ret_0);tag = callbinTM_ret_0}  /* try original pIp -> event */
  if (tag >= 0)  /* found tag method? */
    *(pIp -> ret) = !tagisfalse(tag);
#if defined(LUA_COMPAT_LT_LE)
  else if (pIp -> event == TM_LE) {
    /* try '!(p2 < p1)' for '(p1 <= p2)' */
    pIp -> L->ci->callstatus |= CIST_LEQ;  /* mark it is doing 'lt' for 'le' */
    tag = callbinTM(pIp -> L, pIp -> p2, pIp -> p1, pIp -> L->top.p, TM_LT);
    pIp -> L->ci->callstatus ^= CIST_LEQ;  /* clear mark */
    if (tag >= 0)  /* found tag method? */
      *(pIp -> ret) = tagisfalse(tag);
  }
#endif
  {IPCALL(luaG_ordererror,ipluaG_ordererror_0);}  /* no metamethod found */
  *(pIp -> ret) = 0; /* to avoid warnings */
}