#include "prepCallInfo.h"
void prepCallInfoFun(void *p) 
{
    prepCallInfo *pIp = (prepCallInfo*)p;
  CallInfo ci;{ci = pIp->L->ci = next_ci(pIp->L);}  /* new frame */
  ci->func.p = (pIp->func);
  {lua_assert((pIp->status & ~(CIST_NRESULTS | CIST_C | MAX_CCMT)) == 0);}
  ci->callstatus = (pIp->status);
  ci->top.p = (pIp->top);
  pIp->ret =  ci;
}