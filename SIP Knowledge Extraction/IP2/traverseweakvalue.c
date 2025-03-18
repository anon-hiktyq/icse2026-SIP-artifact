#include "traverseweakvalue.h"
void traverseweakvalueFun(void *p) 
{
    traverseweakvalue *pIp = (traverseweakvalue*)p;
  Node *n, *limit = gnodelast(pIp -> h);
  /* if there is array part, assume it may have white values (it is not
     worth traversing it now just to check) */
  int hasclears = (pIp -> h->asize > 0);
  for (n = gnode(pIp -> h, 0); n < limit; n++) {  /* traverse hash part */
    if (isempty(gval(n)))  /* entry is empty? */
      clearkey(n);  /* clear its key */
    else {
      lua_assert(!keyisnil(n));
      markkey(pIp -> g, n);
      {int iscleared_ret_0;IPCALL(iscleared,ipiscleared_0,.pIp->g = pIp->pIp->g,.o = gcvalueN(gval(n)),.ret = &iscleared_ret_0);if (!hasclears && (iscleared_ret_0)  /* a white value? */
        hasclears = 1}  /* table will have to be cleared */
    }
  }
  if (pIp -> g->gcstate == GCSatomic && hasclears)
    linkgclist(pIp -> h, pIp -> g->weak);  /* has to be cleared later */
  else
    {IPCALL(linkgclist_,iplinkgclist__0,.o = h,.pnext = g->grayagain);}  /* must retraverse it in atomic phase */
}