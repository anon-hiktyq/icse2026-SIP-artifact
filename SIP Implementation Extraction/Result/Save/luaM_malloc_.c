#include "luaM_malloc_.h"
void luaM_malloc_Fun(void *p) 
{
    luaM_malloc_ *pIp = (luaM_malloc_*)p;
  if ((pIp->size) == 0)
    pIp->ret =  NULL;  /* that's all */
  else {
    global_State g;{g = G(pIp->L);}
    void newblock;{newblock = firsttry(g, NULL, cast_sizet(pIp->tag), pIp->size);}
    {if (l_unlikely(newblock == NULL)) {
      {newblock = tryagain(pIp->L, NULL, cast_sizet(pIp->tag), pIp->size);}
      if (newblock == NULL)
        {luaM_error(pIp->L);}
    }}
    {g->GCdebt -= cast(l_mem, pIp->size);}
    pIp->ret =  newblock;
  }
}