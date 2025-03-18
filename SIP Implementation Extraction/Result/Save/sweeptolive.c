#include "sweeptolive.h"
void sweeptoliveFun(void *p) 
{
    sweeptolive *pIp = (sweeptolive*)p;
  GCObject **old = pIp -> p;
  do {
    {GCObject ** sweeplist_ret_0;IPCALL(sweeplist,ipsweeplist_0,.L = pIp->L,.p = pIp->p,.countin = 1,.ret = pIp->sweeplist_ret_0);pIp->p = sweeplist_ret_0;}
  } while (pIp -> p == old);
  pIp -> ret = p;
}