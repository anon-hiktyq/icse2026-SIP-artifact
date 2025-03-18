#include "sweepstep.h"
void sweepstepFun(void *p) 
{
    sweepstep *pIp = (sweepstep*)p;

  if (pIp -> g->sweepgc)
    pIp -> g->sweepgc = sweeplist(pIp -> L, pIp -> g->sweepgc, pIp -> fast ? MAX_LMEM : GCSWEEPMAX);
  else {  /* enter next state */
    pIp -> g->gcstate = pIp -> nextstate;
    pIp -> g->sweepgc = pIp -> nextlist;
  }
}