#include "reinserthash.h"
void reinserthashFun(void *p) 
{
    reinserthash *pIp = (reinserthash*)p;
  unsigned j;
  unsigned size = sizenode(pIp -> ot);
  for (j = 0; j < size; j++) {
    Node *old = gnode(pIp -> ot, j);
    if (!isempty(gval(old))) {
      /* doesn't need barrier/invalidate cache, as entry was
         already present in the table */
      TValue k;
      getnodekey(pIp -> L, &k, old);
      {IPCALL(newcheckedkey,ipnewcheckedkey_0,.pIp->t = pIp->pIp->t,.key = &k,.value = gval(old));}
    }
  }
}