#include "sweepstep.h"
void sweepstepFun(void *p) 
{
    sweepstep *pIp = (sweepstep*)p;
  if ((pIp->g)->sweepgc)
    {GCObject ** sweeplist_ret_0;IPCALL(sweeplist,ipsweeplist_0,.L = pIp->L,.p = g->sweepgc,.countin = fast ? MAX_LMEM : GCSWEEPMAX,.ret = sweeplist_ret_0);pIp->g->sweepgc = sweeplist_ret_0;}
  else {  /* enter next state */
    (pIp->g)->gcstate = (pIp->nextstate);
    (pIp->g)->sweepgc = (pIp->nextlist);
  }
}