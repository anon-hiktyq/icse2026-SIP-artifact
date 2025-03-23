#include "luaC_checkfinalizer.h"
void luaC_checkfinalizerFun(void *p) 
{
    luaC_checkfinalizer *pIp = (luaC_checkfinalizer*)p;
  global_State g;{g = G(pIp->L);}
  {if (tofinalize(pIp->o) ||                 /* obj. is already marked... */
      gfasttm(g, pIp->mt, TM_GC) == NULL ||    /* or has no finalizer... */
      (g->gcstp & GCSTPCLS))                   /* or closing state? */
    return;  /* nothing to be done */
  else {  /* move 'o' to 'finobj' list */
    GCObject **p;
    {if (issweepphase(g)) {
      {makewhite(g, pIp->o);}  /* "sweep" object 'o' */
      if (g->sweepgc == &(pIp->o)->next)  /* should not remove 'sweepgc' object */
        {GCObject ** sweeptolive_ret_0;IPCALL(sweeptolive,ipsweeptolive_0,.L = pIp->L,.p = g->sweepgc,.ret = sweeptolive_ret_0);g->sweepgc = sweeptolive_ret_0;}  /* change 'sweepgc' */
    }
    else
      {IPCALL(correctpointers,ipcorrectpointers_0,.g = g,.o = pIp->o);}}
    /* search for pointer pointing to 'o' */
    for (p = &g->allgc; *p != (pIp->o); p = &(*p)->next) { /* empty */ }
    *p = (pIp->o)->next;  /* remove 'o' from 'allgc' list */
    (pIp->o)->next = g->finobj;  /* link it in 'finobj' list */
    g->finobj = (pIp->o);
    {l_setbit(pIp->o->marked, FINALIZEDBIT);}  /* mark it as such */
  }}
}