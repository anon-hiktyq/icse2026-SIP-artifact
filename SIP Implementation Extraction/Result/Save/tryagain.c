#include "tryagain.h"
void tryagainFun(void *p) 
{
    tryagain *pIp = (tryagain*)p;
  global_State g;{g = G(pIp->L);}
  {if (cantryagain(g)) {
    {IPCALL(luaC_fullgc,ipluaC_fullgc_0);}  /* try to free some memory... */
    pIp->ret =  callfrealloc(g, block, osize, nsize);  /* try again */
  }
  else pIp->ret =  NULL; } /* cannot run an emergency collection */
}