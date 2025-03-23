#include "luaC_barrier_.h"
void luaC_barrier_Fun(void *p) 
{
    luaC_barrier_ *pIp = (luaC_barrier_*)p;
  global_State g;{g = G(pIp->L);}
  {lua_assert(isblack(pIp->o) && iswhite(pIp->v) && !isdead(g, pIp->v) && !isdead(g, pIp->o));}
  {if (keepinvariant(g)) {  /* must keep invariant? */
    {IPCALL(reallymarkobject,ipreallymarkobject_0,.g = g,.o = pIp->v);}  /* restore invariant */
    {if (isold(pIp->o)) {
      {lua_assert(!isold(pIp->v));}  /* white object could not be old */
      {setage(pIp->v, G_OLD0);}  /* restore generational invariant */
    }}
  }
  else {  /* sweep phase */
    {lua_assert(issweepphase(g));}
    if (g->gckind != KGC_GENMINOR)  /* incremental mode? */
      {makewhite(g, pIp->o);}  /* mark 'o' as white to avoid other barriers */
  }}
}