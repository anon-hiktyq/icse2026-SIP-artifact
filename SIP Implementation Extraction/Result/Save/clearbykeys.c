#include "clearbykeys.h"
void clearbykeysFun(void *p) 
{
    clearbykeys *pIp = (clearbykeys*)p;
  for (; pIp -> l; pIp -> l = gco2t(pIp -> l)->gclist) {
    Table *h = gco2t(pIp -> l);
    Node *limit = gnodelast(h);
    Node *n;
    for (n = gnode(h, 0); n < limit; n++) {
      {int iscleared_ret_0;IPCALL(iscleared,ipiscleared_0,.pIp->g = pIp->pIp->g,.o = gckeyN(n),.ret = &iscleared_ret_0);if ((iscleared_ret_0)  /* unmarked key? */
        setempty(gval(n))}  /* remove entry */
      if (isempty(gval(n)))  /* is entry empty? */
        {IPCALL(clearkey,ipclearkey_0,.n = n);}  /* clear its key */
    }
  }
}