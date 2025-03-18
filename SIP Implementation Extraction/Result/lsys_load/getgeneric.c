#include "getgeneric.h"
void getgenericFun(void *p) 
{
    getgeneric *pIp = (getgeneric*)p;
  Node *n;{Node * mainpositionTV_ret_1;IPCALL(mainpositionTV,ipmainpositionTV_0,.t = pIp->t,.key = pIp->key,.ret = pIp->mainpositionTV_ret_1);*n = mainpositionTV_ret_1}
  for (;;) {  /* check whether 'pIp -> key' is somewhere in the chain */
    {int equalkey_ret_0;IPCALL(equalkey,ipequalkey_0,.k1 = key,.n2 = n,.deadok = pIp->deadok,.ret = pIp->&equalkey_ret_0);if ((equalkey_ret_0)
      pIp -> ret = gval(n); /* that's it */
    else {
      int nx = gnext(n);
      if (nx == 0)
        pIp -> ret = &absentkey; /* not found */
      n += nx;
    }}
  }
}