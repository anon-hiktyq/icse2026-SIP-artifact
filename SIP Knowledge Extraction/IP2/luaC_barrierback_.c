#include "luaC_barrierback_.h"
void luaC_barrierback_Fun(void *p) 
{
    luaC_barrierback_ *pIp = (luaC_barrierback_*)p;
  global_State *g = G(pIp -> L);
  lua_assert(isblack(pIp -> o) && !isdead(g, pIp -> o));
  lua_assert((g->gckind != KGC_GENMINOR)
          || (isold(pIp -> o) && getage(pIp -> o) != G_TOUCHED1));
  if (getage(pIp -> o) == G_TOUCHED2)  /* already in gray list? */
    set2gray(pIp -> o);  /* make it gray to become touched1 */
  else  /* link it in 'grayagain' and paint it gray */
    linkobjgclist(pIp -> o, g->grayagain);
  if (isold(pIp -> o))  /* generational mode? */
    setage(pIp -> o, G_TOUCHED1);  /* touched in current cycle */
}