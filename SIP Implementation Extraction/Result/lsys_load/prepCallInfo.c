#include "prepCallInfo.h"
void prepCallInfoFun(void *p) 
{
    prepCallInfo *pIp = (prepCallInfo*)p;

  CallInfo pIp -> *ci = pIp -> L->pIp -> ci = next_ci(pIp -> L);  /* new frame */
  pIp -> ci->pIp -> func.p = pIp -> func;
  lua_assert((pIp -> status & ~(CIST_NRESULTS | CIST_C | MAX_CCMT)) == 0);
  pIp -> ci->callstatus = pIp -> status;
  pIp -> ci->pIp -> top.p = pIp -> top;
  pIp -> ret = ci;
}