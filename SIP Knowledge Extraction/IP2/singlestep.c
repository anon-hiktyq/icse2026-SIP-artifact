#include "singlestep.h"
void singlestepFun(void *p) 
{
    singlestep *pIp = (singlestep*)p;
  global_State *g = G(pIp -> L);
  l_mem stepresult;
  lua_assert(!g->gcstopem);  /* collector is not reentrant */
  g->gcstopem = 1;  /* no emergency collections while collecting */
  switch (g->gcstate) {
    case GCSpause: {
      {IPCALL(restartcollection,iprestartcollection_0,.g = g);}
      g->gcstate = GCSpropagate;
      stepresult = 1;
      break;
    }
    case GCSpropagate: {
      if (pIp -> fast || g->gray == NULL) {
        g->gcstate = GCSenteratomic;  /* finish propagate phase */
        stepresult = 1;
      }
      else
        stepresult = propagatemark(g);  /* traverse one gray object */
      break;
    }
    case GCSenteratomic: {
      {IPCALL(atomic,ipatomic_0,.L = pIp->L);}
      {int checkmajorminor_ret_0;IPCALL(checkmajorminor,ipcheckmajorminor_0,.L = pIp->L,.g = g,.ret = pIp->&checkmajorminor_ret_0);if ((checkmajorminor_ret_0)
        stepresult = step2minor;
      else {
        {IPCALL(entersweep,ipentersweep_0,.L = pIp->L);}
        stepresult = atomicstep;
      }}
      break;
    }
    case GCSswpallgc: {  /* sweep "regular" objects */
      {IPCALL(sweepstep,ipsweepstep_2,.L = pIp->L,.g = g,.nextstate = GCSswpfinobj,.nextlist = &g->finobj,.fast = pIp->fast);}
      stepresult = GCSWEEPMAX;
      break;
    }
    case GCSswpfinobj: {  /* sweep objects with finalizers */
      {IPCALL(sweepstep,ipsweepstep_1,.L = pIp->L,.g = g,.nextstate = GCSswptobefnz,.nextlist = &g->tobefnz,.fast = pIp->fast);}
      stepresult = GCSWEEPMAX;
      break;
    }
    case GCSswptobefnz: {  /* sweep objects to be finalized */
      {IPCALL(sweepstep,ipsweepstep_0,.L = pIp->L,.g = g,.nextstate = GCSswpend,.nextlist = NULL,.fast = pIp->fast);}
      stepresult = GCSWEEPMAX;
      break;
    }
    case GCSswpend: {  /* finish sweeps */
      {IPCALL(checkSizes,ipcheckSizes_0,.L = pIp->L,.g = g);}
      g->gcstate = GCScallfin;
      stepresult = GCSWEEPMAX;
      break;
    }
    case GCScallfin: {  /* call finalizers */
      if (g->tobefnz && !g->gcemergency) {
        g->gcstopem = 0;  /* ok collections during finalizers */
        {IPCALL(GCTM,ipGCTM_0,.L = pIp->L);}  /* call one finalizer */
        stepresult = CWUFIN;
      }
      else {  /* emergency mode or no more finalizers */
        g->gcstate = GCSpause;  /* finish collection */
        stepresult = step2pause;
      }
      break;
    }
    default: lua_assert(0); return 0;
  }
  g->gcstopem = 0;
  *(pIp -> ret) = stepresult;
}