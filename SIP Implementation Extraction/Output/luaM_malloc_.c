#include "luaM_malloc_.h"
void luaM_malloc_Fun(void *p) 
{
    luaM_malloc_ *pIp = (luaM_malloc_*)p;
  if (pIp -> size == 0)
    pIp -> ret = NULL; /* that's all */
  else {
    global_State *g = G(pIp -> L);
    void *newblock = firsttry(g, NULL, cast_sizet(pIp -> tag), pIp -> size);
    if (l_unlikely(newblock == NULL)) {
      {void * tryagain_ret_0;IPCALL(tryagain,iptryagain_0,.pIp->L = pIp->pIp->L,.block = NULL,.osize = cast_sizet(pIp->tag),.nsize = pIp->size,.pIp->ret = pIp->tryagain_ret_0);newblock = tryagain_ret_0;}
      if (newblock == NULL)
        luaM_error(pIp -> L);
    }
    g->GCdebt -= cast(l_mem, pIp -> size);
    pIp -> ret = newblock;
  }
}