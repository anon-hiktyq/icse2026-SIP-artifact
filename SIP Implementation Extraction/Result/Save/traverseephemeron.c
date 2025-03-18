#include "traverseephemeron.h"
void traverseephemeronFun(void *p) 
{
    traverseephemeron *pIp = (traverseephemeron*)p;
  int hasclears = 0;  /* true if table has white keys */
  int hasww = 0;  /* true if table has entry "white-key -> white-value" */
  unsigned int i;
  unsigned int nsize = sizenode(pIp -> h);
  int marked;{int traversearray_ret_1;IPCALL(traversearray,iptraversearray_0,.g = pIp->g,.h = pIp->h,.ret = pIp->&traversearray_ret_1);marked = traversearray_ret_1}  /* traverse array part */
  /* traverse hash part; if 'inv', traverse descending
     (see 'convergeephemerons') */
  for (i = 0; i < nsize; i++) {
    Node *n = pIp -> inv ? gnode(pIp -> h, nsize - 1 - i) : gnode(pIp -> h, i);
    if (isempty(gval(n)))  /* entry is empty? */
      clearkey(n);  /* clear its key */
    else {int iscleared_ret_0;IPCALL(iscleared,ipiscleared_0,.pIp->g = pIp->pIp->g,.o = gckeyN(n),.pIp->ret = pIp->&iscleared_ret_0);if ((iscleared_ret_0) {  /* key is not marked (yet)? */
      hasclears = 1;  /* table must be cleared */
      if (valiswhite(gval(n)))  /* value not marked yet? */
        hasww = 1;  /* white-white entry */
    }
    else if (valiswhite(gval(n))) {  /* value not marked yet? */
      marked = 1;
      reallymarkobject(pIp -> g, gcvalue(gval(n)));  /* mark it now */
    }}
  }
  /* link table into proper list */
  if (pIp -> g->gcstate == GCSpropagate)
    linkgclist(pIp -> h, pIp -> g->grayagain);  /* must retraverse it in atomic phase */
  else if (hasww)  /* table has white->white entries? */
    linkgclist(pIp -> h, pIp -> g->ephemeron);  /* have to propagate again */
  else if (hasclears)  /* table has white keys? */
    linkgclist(pIp -> h, pIp -> g->allweak);  /* may have to clean white keys */
  else
    {IPCALL(genlink,ipgenlink_0,.pIp->g = pIp->pIp->g,.o = obj2gco(pIp->h));}  /* check whether collector still needs to see it */
  *(pIp -> ret) = marked;
}