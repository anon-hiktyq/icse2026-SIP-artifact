#include "incstep.h"
void incstepFun(void *p) 
{
    incstep *pIp = (incstep*)p;
  l_mem stepsize;{stepsize = applygcparam(pIp->g, STEPSIZE, 100);}
  l_mem work2do;{work2do = applygcparam(pIp->g, STEPMUL, stepsize / cast_int(sizeof(void*)));}
  l_mem stres;
  int fast = (work2do == 0);  /* special case: do a full collection */
  do {  /* repeat until enough work */
    {l_mem singlestep_ret_0;IPCALL(singlestep,ipsinglestep_0,.L = pIp->L,.fast = fast,.ret = &singlestep_ret_0);stres = singlestep_ret_0;}  /* perform one single step */
    if (stres == step2minor)  /* returned to minor collections? */
      return;  /* nothing else to be done here */
    else if (stres == step2pause || (stres == atomicstep && !fast))
      break;  /* end of cycle or atomic */
    else
      work2do -= stres;
  } while (fast || work2do > 0);
  if ((pIp->g)->gcstate == GCSpause)
    {IPCALL(setpause,ipsetpause_0,.g = pIp->g);}  /* pause until next cycle */
  else
    {IPCALL(luaE_setdebt,ipluaE_setdebt_0);}
}