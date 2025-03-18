#include "freestack.h"
void freestackFun(void *p) 
{
    freestack *pIp = (freestack*)p;
  if (pIp -> L->stack.p == NULL)
    return;  /* stack not completely built yet */
  pIp -> L->ci = pIp -> &L->base_ci;  /* free the entire 'ci' list */
  {IPCALL(freeCI,ipfreeCI_0,.L = pIp->L);}
  lua_assert(pIp -> L->nci == 0);
  /* free stack */
  luaM_freearray(pIp -> L, pIp -> L->stack.p, cast_sizet(stacksize(pIp -> L) + EXTRA_STACK));
}