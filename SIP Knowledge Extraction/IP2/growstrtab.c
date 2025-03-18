#include "growstrtab.h"
void growstrtabFun(void *p) 
{
    growstrtab *pIp = (growstrtab*)p;
  if (l_unlikely(pIp -> tb->nuse == INT_MAX)) {  /* too many strings? */
    {IPCALL(luaC_fullgc,ipluaC_fullgc_0);}  /* try to free some... */
    if (pIp -> tb->nuse == INT_MAX)  /* still too many? */
      luaM_error(pIp -> L);  /* cannot even create a message... */
  }
  if (pIp -> tb->size <= MAXSTRTB / 2)  /* can grow string table? */
    {IPCALL(luaS_resize,ipluaS_resize_0,.L = pIp->L,.nsize = tb->size * 2);}
}