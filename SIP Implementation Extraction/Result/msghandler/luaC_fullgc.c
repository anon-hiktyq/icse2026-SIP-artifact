#include "luaC_fullgc.h"
void luaC_fullgcFun(void *p) 
{
    luaC_fullgc *pIp = (luaC_fullgc*)p;
  global_State g;{g = G(pIp->L);}
  {lua_assert(!g->gcemergency);}
  {g->gcemergency = cast_byte(pIp->isemergency);}  /* set flag */
  switch (g->gckind) {
    case KGC_GENMINOR: {IPCALL(fullgen,ipfullgen_0,.L = pIp->L,.g = g);} break;
    case KGC_INC: {IPCALL(fullinc,ipfullinc_0,.L = pIp->L,.g = g);} break;
    case KGC_GENMAJOR:
      g->gckind = KGC_INC;
      {IPCALL(fullinc,ipfullinc_1,.L = pIp->L,.g = g);}
      g->gckind = KGC_GENMAJOR;
      break;
  }
  g->gcemergency = 0;
}