#include "entersweep.h"
void entersweepFun(void *p) 
{
    entersweep *pIp = (entersweep*)p;
  global_State *g = G(pIp -> L);
  g->gcstate = GCSswpallgc;
  lua_assert(g->sweepgc == NULL);
  {GCObject ** sweeptolive_ret_0;IPCALL(sweeptolive,ipsweeptolive_0,.L = pIp->L,.p = &g->allgc,.ret = sweeptolive_ret_0);g->sweepgc = sweeptolive_ret_0;}
}