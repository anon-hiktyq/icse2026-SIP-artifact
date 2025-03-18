#include "luaD_poscall.h"
void luaD_poscallFun(void *p) 
{
    luaD_poscall *pIp = (luaD_poscall*)p;
  l_uint32 fwanted = pIp -> ci->callstatus & (CIST_TBC | CIST_NRESULTS);
  if (l_unlikely(pIp -> L->hookmask) && !(fwanted & CIST_TBC))
    {IPCALL(rethook,iprethook_0,.L = pIp->L,.ci = pIp->ci,.nres = pIp->nres);}
  /* move results to proper place */
  {IPCALL(moveresults,ipmoveresults_0,.L = pIp->L,.res = ci->func.p,.nres = pIp->nres,.fwanted = fwanted);}
  /* function cannot be in any of these cases when returning */
  lua_assert(!(pIp -> ci->callstatus &
        (CIST_HOOKED | CIST_YPCALL | CIST_FIN | CIST_CLSRET)));
  pIp -> L->pIp -> ci = pIp -> ci->previous;  /* back to caller (after closing variables) */
}