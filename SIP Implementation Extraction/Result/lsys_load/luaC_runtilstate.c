#include "luaC_runtilstate.h"
void luaC_runtilstateFun(void *p) 
{
    luaC_runtilstate *pIp = (luaC_runtilstate*)p;
  global_State *g = G(pIp -> L);
  lua_assert(g->gckind == KGC_INC);
  while (pIp -> state != g->gcstate)
    {l_mem singlestep_ret_0;IPCALL(singlestep,ipsinglestep_0,.L = pIp->L,.fast = pIp->fast,.ret = &singlestep_ret_0);}
}