#include "luaM_saferealloc_.h"
void luaM_saferealloc_Fun(void *p) 
{
    luaM_saferealloc_ *pIp = (luaM_saferealloc_*)p;

  void *pIp->newblock;{void * luaM_realloc__ret_0;IPCALL(luaM_realloc_,ipluaM_realloc__0,.L = pIp->L,.block = pIp->block,.osize = pIp->osize,.nsize = pIp->nsize,.ret = pIp->luaM_realloc__ret_0);*pIp->newblock = luaM_realloc__ret_0}
  if (l_unlikely(pIp -> newblock == NULL && pIp -> nsize > 0))  /* allocation failed? */
    luaM_error(pIp -> L);
  pIp -> ret = newblock;
}