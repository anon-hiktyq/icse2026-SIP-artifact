#include "entergen.h"
void entergenFun(void *p) 
{
    entergen *pIp = (entergen*)p;
  {IPCALL(luaC_runtilstate,ipluaC_runtilstate_1,.L = pIp->L,.state = GCSpause,.fast = 1);}  /* prepare to start a new cycle */
  {IPCALL(luaC_runtilstate,ipluaC_runtilstate_0,.L = pIp->L,.state = GCSpropagate,.fast = 1);}  /* start new cycle */
  {IPCALL(atomic,ipatomic_0,.L = pIp->L);}  /* propagates all and then do the atomic stuff */
  {IPCALL(atomic2gen,ipatomic2gen_0,.L = pIp->L,.g = pIp->g);}
  {IPCALL(setminordebt,ipsetminordebt_0,.g = pIp->g);}  /* set debt assuming next cycle will be minor */
}