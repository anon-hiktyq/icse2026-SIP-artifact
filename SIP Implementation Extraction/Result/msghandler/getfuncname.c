#include "getfuncname.h"
void getfuncnameFun(void *p) 
{
    getfuncname *pIp = (getfuncname*)p;
  /* calling function is a known function? */
  if ((pIp->ci) != NULL && !((pIp->ci)->callstatus & CIST_TAIL))
    const char * funcnamefromcall_ret_0;IPCALL(funcnamefromcall,ipfuncnamefromcall_0,.L = pIp->L,.ci = ci->previous,.name = pIp->name,.ret = funcnamefromcall_ret_0);pIp->ret =  funcnamefromcall_ret_0;
  else pIp->ret =  NULL;  /* no way to find a name */
}