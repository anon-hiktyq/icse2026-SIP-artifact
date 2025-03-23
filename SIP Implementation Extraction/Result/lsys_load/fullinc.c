#include "fullinc.h"
void fullincFun(void *p) 
{
    fullinc *pIp = (fullinc*)p;
  {if (keepinvariant(pIp->g))  /* black objects? */
    {IPCALL(entersweep,ipentersweep_0,.L = pIp->L);}} /* sweep everything to turn them back to white */
  /* finish any pending sweep phase to start a new cycle */
  {IPCALL(luaC_runtilstate,ipluaC_runtilstate_0,.L = pIp->L,.state = GCSpause,.fast = 1);}
  {IPCALL(luaC_runtilstate,ipluaC_runtilstate_2,.L = pIp->L,.state = GCScallfin,.fast = 1);}  /* run up to finalizers */
  {IPCALL(luaC_runtilstate,ipluaC_runtilstate_1,.L = pIp->L,.state = GCSpause,.fast = 1);}  /* finish collection */
  {IPCALL(setpause,ipsetpause_0,.g = pIp->g);}
}