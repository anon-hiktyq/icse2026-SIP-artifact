#include "ccall.h"
void ccallFun(void *p) 
{
    ccall *pIp = (ccall*)p;
  CallInfo *ci;
  pIp -> L->nCcalls += pIp -> inc;
  if (l_unlikely(getCcalls(pIp -> L) >= LUAI_MAXCCALLS)) {
    checkstackp(pIp -> L, 0, pIp -> func);  /* free any use of EXTRA_STACK */
    {IPCALL(luaE_checkcstack,ipluaE_checkcstack_0);}
  }
  {CallInfo * luaD_precall_ret_0;IPCALL(luaD_precall,ipluaD_precall_0,.L = pIp->L,.func = pIp->func,.nresults = nResults,.ret = luaD_precall_ret_0);if ((ci = (luaD_precall_ret_0) != NULL) {  /* Lua function? */
    ci->callstatus |= CIST_FRESH;  /* mark that it is a "fresh" execute */
    {IPCALL(luaV_execute,ipluaV_execute_0);}  /* call it */
  }}
  pIp -> L->nCcalls -= pIp -> inc;
}