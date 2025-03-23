#include "clearNewSlice.h"
void clearNewSliceFun(void *p) 
{
    clearNewSlice *pIp = (clearNewSlice*)p;
  for (; (pIp->oldasize) < (pIp->newasize); (pIp->oldasize)++)
    {*getArrTag(pIp->t, pIp->oldasize) = LUA_VEMPTY;}
}