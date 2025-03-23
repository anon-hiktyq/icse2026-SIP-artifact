#include "traverseweakvalue.h"
void traverseweakvalueFun(void *p) 
{
    traverseweakvalue *pIp = (traverseweakvalue*)p;
  Node limit;{limit = gnodelast(pIp->h);}
  /* if there is array part, assume it may have white values (it is not
     worth traversing it now just to check) */
  int hasclears = ((pIp->h)->asize > 0);
  for (n = gnode((pIp->h), 0); n < limit; n++) {  /* traverse hash part */
    {if (isempty(gval(n)))  /* entry is empty? */
      {IPCALL(clearkey,ipclearkey_0,.n = n);}  /* clear its key */
    else {
      {lua_assert(!keyisnil(n));}
      {markkey(pIp->g, n);}
      {if (!hasclears && iscleared(pIp->g, gcvalueN(gval(n))))  /* a white value? */
        hasclears = 1; } /* table will have to be cleared */
    }}
  }
  if ((pIp->g)->gcstate == GCSatomic && hasclears)
    {linkgclist(pIp->h, pIp->g->weak);}  /* has to be cleared later */
  else
    {linkgclist(pIp->h, pIp->g->grayagain);}  /* must retraverse it in atomic phase */
}