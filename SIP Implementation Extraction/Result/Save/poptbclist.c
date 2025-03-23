#include "poptbclist.h"
void poptbclistFun(void *p) 
{
    poptbclist *pIp = (poptbclist*)p;
  StkId tbc = (pIp->L)->tbclist.p;
  {lua_assert(tbc->tbclist.delta > 0);}  /* first element cannot be dummy */
  tbc -= tbc->tbclist.delta;
  while (tbc > (pIp->L)->stack.p && tbc->tbclist.delta == 0)
    tbc -= MAXDELTA;  /* remove dummy nodes */
  (pIp->L)->tbclist.p = tbc;
}