#include "getfuncname.h"
void getfuncnameFun(void *p) 
{
    getfuncname *pIp = (getfuncname*)p;
  /* calling function is a known function? */
  if (pIp -> ci != NULL && !(pIp -> ci->callstatus & CIST_TAIL))
    pIp -> ret = funcnamefromcall(L, ci->previous, name);
  else return NULL;  /* no way to find a pIp -> name */
}