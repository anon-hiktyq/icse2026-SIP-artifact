#include "clearbyvalues.h"
void clearbyvaluesFun(void *p) 
{
    clearbyvalues *pIp = (clearbyvalues*)p;
  for (; (pIp->l) != (pIp->f); (pIp->l) = gco2t((pIp->l))->gclist) {
    Table h;{h = gco2t(pIp->l);}
    Node limit;{limit = gnodelast(h);}
    unsigned int i;
    unsigned int asize = h->asize;
    for (i = 0; i < asize; i++) {
      GCObject o;{o = gcvalarr(h, i);}
      {int iscleared_ret_0;IPCALL(iscleared,ipiscleared_0,.g = pIp->g,.o = o,.ret = &iscleared_ret_0);if (iscleared_ret_0)  /* value was collected? */
        {*getArrTag(h, i) = LUA_VEMPTY;}}  /* remove entry */
    }
    for (n = gnode(h, 0); n < limit; n++) {
      {if (iscleared(pIp->g, gcvalueN(gval(n))))  /* unmarked value? */
        {setempty(gval(n));}}  /* remove entry */
      {if (isempty(gval(n)))  /* is entry empty? */
        {IPCALL(clearkey,ipclearkey_0,.n = n);}}  /* clear its key */
    }
  }
}