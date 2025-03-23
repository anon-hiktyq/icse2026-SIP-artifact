#include "clearbykeys.h"
void clearbykeysFun(void *p) 
{
    clearbykeys *pIp = (clearbykeys*)p;
  for (; (pIp->l); (pIp->l) = gco2t((pIp->l))->gclist) {
    Table h;{h = gco2t(pIp->l);}
    Node limit;{limit = gnodelast(h);}
    Node *n;
    for (n = gnode(h, 0); n < limit; n++) {
      {if (iscleared(pIp->g, gckeyN(n)))  /* unmarked key? */
        {setempty(gval(n));}}  /* remove entry */
      {if (isempty(gval(n)))  /* is entry empty? */
        {IPCALL(clearkey,ipclearkey_0,.n = n);}}  /* clear its key */
    }
  }
}