#include "luaM_free_.h"
void luaM_free_Fun(void *p) 
{
    luaM_free_ *pIp = (luaM_free_*)p;
  global_State g;{g = G(pIp->L);}
  {lua_assert((pIp->osize == 0) == (pIp->block == NULL));}
  {callfrealloc(g, pIp->block, pIp->osize, 0);}
  {g->GCdebt += cast(l_mem, pIp->osize);}
}