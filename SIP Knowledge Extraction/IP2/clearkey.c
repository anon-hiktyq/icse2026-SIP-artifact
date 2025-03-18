#include "clearkey.h"
void clearkeyFun(void *p) 
{
    clearkey *pIp = (clearkey*)p;
  lua_assert(isempty(gval(pIp -> n)));
  if (keyiscollectable(pIp -> n))
    setdeadkey(pIp -> n);  /* unused key; remove it */
}