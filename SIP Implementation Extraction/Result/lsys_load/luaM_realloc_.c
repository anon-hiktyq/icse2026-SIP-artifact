#include "luaM_realloc_.h"
void luaM_realloc_Fun(void *p) 
{
    luaM_realloc_ *pIp = (luaM_realloc_*)p;
  void *newblock;
  global_State *g = G(pIp -> L);
  lua_assert((pIp -> osize == 0) == (pIp -> block == NULL));
  newblock = firsttry(g, pIp -> block, pIp -> osize, pIp -> nsize);
  if (l_unlikely(newblock == NULL && pIp -> nsize > 0)) {
    {void * tryagain_ret_0;IPCALL(tryagain,iptryagain_0,.L = pIp->L,.block = pIp->block,.osize = pIp->osize,.nsize = pIp->nsize,.ret = pIp->tryagain_ret_0);newblock = tryagain_ret_0;}
    if (newblock == NULL)  /* still no memory? */
      pIp -> ret = NULL; /* do not update 'GCdebt' */
  }
  lua_assert((pIp -> nsize == 0) == (newblock == NULL));
  g->GCdebt -= cast(l_mem, pIp -> nsize) - cast(l_mem, pIp -> osize);
  pIp -> ret = newblock;
}