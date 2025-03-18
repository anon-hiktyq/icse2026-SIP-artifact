#include "clearbyvalues.h"
void clearbyvaluesFun(void *p) 
{
    clearbyvalues *pIp = (clearbyvalues*)p;
  for (; pIp -> l != pIp -> f; pIp -> l = gco2t(pIp -> l)->gclist) {
    Table *h = gco2t(pIp -> l);
    Node *n, *limit = gnodelast(h);
    unsigned int i;
    unsigned int asize = h->asize;
    for (i = 0; i < asize; i++) {
      GCObject *o = gcvalarr(h, i);
      {int iscleared_ret_1;IPCALL(iscleared,ipiscleared_1,.g = pIp->g,.o = o,.ret = &iscleared_ret_1);if ((iscleared_ret_1)  /* value was collected? */
        *getArrTag(h, i) = LUA_VEMPTY}  /* remove entry */
    }
    for (n = gnode(h, 0); n < limit; n++) {
      {int iscleared_ret_0;IPCALL(iscleared,ipiscleared_0,.pIp->g = pIp->pIp->g,.o = gcvalueN(gval(n)),.ret = &iscleared_ret_0);if ((iscleared_ret_0)  /* unmarked value? */
        setempty(gval(n))}  /* remove entry */
      if (isempty(gval(n)))  /* is entry empty? */
        {IPCALL(clearkey,ipclearkey_0,.n = n);}  /* clear its key */
    }
  }
}