#include "funcnamefromcall.h"
void funcnamefromcallFun(void *p) 
{
    funcnamefromcall *pIp = (funcnamefromcall*)p;
  if ((pIp->ci)->callstatus & CIST_HOOKED) {  /* was it called inside a hook? */
    *(pIp->name) = "?";
    pIp->ret =  "hook";
  }
  else if ((pIp->ci)->callstatus & CIST_FIN) {  /* was it called as a finalizer? */
    *(pIp->name) = "__gc";
    pIp->ret =  "metamethod";  /* report it as such */
  }
  else {if (isLua(pIp->ci))
    pIp->ret =  funcnamefromcode(L, ci_func(ci)->p, currentpc(ci), name);
  else
    pIp->ret =  NULL;}
}