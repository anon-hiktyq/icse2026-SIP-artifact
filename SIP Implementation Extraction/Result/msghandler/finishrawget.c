#include "finishrawget.h"
void finishrawgetFun(void *p) 
{
    finishrawget *pIp = (finishrawget*)p;
  {if (tagisempty(pIp->tag))  /* avoid copying empty items to the stack */
    {setnilvalue(s2v(pIp->L->top.p));}}
  {api_incr_top(pIp->L);}
  {lua_unlock(pIp->L);}
  *(pIp->ret) =  novariant(tag);
}