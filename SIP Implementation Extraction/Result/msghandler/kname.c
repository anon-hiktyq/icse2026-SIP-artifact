#include "kname.h"
void knameFun(void *p) 
{
    kname *pIp = (kname*)p;
  TValue *kvalue = &(pIp->p)->k[(pIp->index)];
  {if (ttisstring(kvalue)) {
    {*pIp->name = getstr(tsvalue(kvalue));}
    pIp->ret =  "constant";
  }
  else {
    *(pIp->name) = "?";
    pIp->ret =  NULL;
  }}
}