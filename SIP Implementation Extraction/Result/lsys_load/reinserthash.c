#include "reinserthash.h"
void reinserthashFun(void *p) 
{
    reinserthash *pIp = (reinserthash*)p;
  unsigned j;
  unsigned size;{size = sizenode(pIp->ot);}
  for (j = 0; j < size; j++) {
    Node old;{old = gnode(pIp->ot, j);}
    {if (!isempty(gval(old))) {
      /* doesn't need barrier/invalidate cache, as entry was
         already present in the table */
      TValue k;
      {getnodekey(pIp->L, &k, old);}
      {newcheckedkey(pIp->t, &k, gval(old));}
    }}
  }
}