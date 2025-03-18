#include "udata2finalize.h"
void udata2finalizeFun(void *p) 
{
    udata2finalize *pIp = (udata2finalize*)p;
  GCObject *o = pIp -> g->tobefnz;  /* get first element */
  lua_assert(tofinalize(o));
  pIp -> g->tobefnz = o->next;  /* remove it from 'tobefnz' list */
  o->next = pIp -> g->allgc;  /* return it to 'allgc' list */
  pIp -> g->allgc = o;
  resetbit(o->marked, FINALIZEDBIT);  /* object is "normal" again */
  if (issweepphase(pIp -> g))
    makewhite(pIp -> g, o);  /* "sweep" object */
  else if (getage(o) == G_OLD1)
    pIp -> g->firstold1 = o;  /* it is the first OLD1 object in the list */
  pIp -> ret = o;
}