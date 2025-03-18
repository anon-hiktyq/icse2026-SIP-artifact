#include "udata2finalize.h"
void udata2finalizeFun(void *p) 
{
    udata2finalize *pIp = (udata2finalize*)p;
  GCObject pIp -> *o = pIp -> g->tobefnz;  /* get first element */
  lua_assert(tofinalize(pIp -> o));
  pIp -> g->tobefnz = pIp -> o->next;  /* remove it from 'tobefnz' list */
  pIp -> o->next = pIp -> g->allgc;  /* return it to 'allgc' list */
  pIp -> g->allgc = pIp -> o;
  resetbit(pIp -> o->marked, FINALIZEDBIT);  /* object is "normal" again */
  if (issweepphase(pIp -> g))
    makewhite(pIp -> g, pIp -> o);  /* "sweep" object */
  else if (getage(pIp -> o) == G_OLD1)
    pIp -> g->firstold1 = pIp -> o;  /* it is the first OLD1 object in the list */
  pIp -> ret = o;
}