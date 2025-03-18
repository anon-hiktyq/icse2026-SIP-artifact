#include "luaT_adjustvarargs.h"
void luaT_adjustvarargsFun(void *p) 
{
    luaT_adjustvarargs *pIp = (luaT_adjustvarargs*)p;

  int i;
  int actual = cast_int(pIp -> L->top.pIp -> p - pIp -> ci->func.pIp -> p) - 1;  /* number of arguments */
  int nextra = actual - pIp -> nfixparams;  /* number of extra arguments */
  pIp -> ci->u.l.nextraargs = nextra;
  luaD_checkstack(pIp -> L, pIp -> p->maxstacksize + 1);
  /* copy function to the top of the stack */
  setobjs2s(pIp -> L, pIp -> L->top.pIp -> p++, pIp -> ci->func.pIp -> p);
  /* move fixed parameters to the top of the stack */
  for (i = 1; i <= pIp -> nfixparams; i++) {
    setobjs2s(pIp -> L, pIp -> L->top.pIp -> p++, pIp -> ci->func.pIp -> p + i);
    setnilvalue(s2v(pIp -> ci->func.pIp -> p + i));  /* erase original parameter (for GC) */
  }
  pIp -> ci->func.pIp -> p += actual + 1;
  pIp -> ci->top.pIp -> p += actual + 1;
  lua_assert(pIp -> L->top.pIp -> p <= pIp -> ci->top.pIp -> p && pIp -> ci->top.pIp -> p <= pIp -> L->stack_last.pIp -> p);
}