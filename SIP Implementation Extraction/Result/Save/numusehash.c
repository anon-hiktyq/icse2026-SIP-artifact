#include "numusehash.h"
void numusehashFun(void *p) 
{
    numusehash *pIp = (numusehash*)p;
  unsigned i;{i = sizenode(pIp->t);}
  unsigned total = 0;
  while (i--) {
    Node *n = &(pIp->t)->node[i];
    {if (isempty(gval(n))) {
      {lua_assert(!keyisnil(n));}  /* entry was deleted; key cannot be nil */
      (pIp->ct)->deleted = 1;
    }
    else {
      total++;
      {if (keyisinteger(n))
        {countint(keyival(n), pIp->ct);}}
    }}
  }
  (pIp->ct)->total += total;
}