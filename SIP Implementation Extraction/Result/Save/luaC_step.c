#include "luaC_step.h"
void luaC_stepFun(void *p) 
{
    luaC_step *pIp = (luaC_step*)p;
  global_State *g = G(pIp -> L);
  lua_assert(!g->gcemergency);
  if (!gcrunning(g)) {  /* not running? */
    if (g->gcstp & GCSTPUSR)  /* stopped by the user? */
      {IPCALL(luaE_setdebt,ipluaE_setdebt_0);}
  }
  else {
    luai_tracegc(pIp -> L, 1);  /* for internal debugging */
    switch (g->gckind) {
      case KGC_INC: case KGC_GENMAJOR:
        incstep(pIp -> L, g);
        break;
      case KGC_GENMINOR:
        youngcollection(pIp -> L, g);
        setminordebt(g);
        break;
    }
    luai_tracegc(pIp -> L, 0);  /* for internal debugging */
  }
}