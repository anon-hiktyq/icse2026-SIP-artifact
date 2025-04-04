#include "luaC_changemode.h"
void luaC_changemodeFun(void *p) 
{
    luaC_changemode *pIp = (luaC_changemode*)p;
  global_State g;{g = G(pIp->L);}
  if (g->gckind == KGC_GENMAJOR)  /* doing major collections? */
    g->gckind = KGC_INC;  /* already incremental but in name */
  if ((pIp->newmode) != g->gckind) {  /* does it need to change? */
    if ((pIp->newmode) == KGC_INC)  /* entering incremental mode? */
      {IPCALL(minor2inc,ipminor2inc_0,.L = pIp->L,.g = g,.kind = KGC_INC);}  /* entering incremental mode */
    else {
      {lua_assert(pIp->newmode == KGC_GENMINOR);}
      {IPCALL(entergen,ipentergen_0,.L = pIp->L,.g = g);}
    }
  }
}