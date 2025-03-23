#include "reverse.h"
void reverseFun(void *p) 
{
    reverse *pIp = (reverse*)p;
  for (; (pIp->from) < (pIp->to); (pIp->from)++, (pIp->to)--) {
    TValue temp;
    {setobj(pIp->L, &temp, s2v(pIp->from));}
    {setobjs2s(pIp->L, pIp->from, pIp->to);}
    {setobj2s(pIp->L, pIp->to, &temp);}
  }
}