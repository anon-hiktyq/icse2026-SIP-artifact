#include "luaE_extendCI.h"
void luaE_extendCIFun(void *p) 
{
    luaE_extendCI *pIp = (luaE_extendCI*)p;
  CallInfo *ci;
  lua_assert(pIp -> L->ci->next == NULL);
  ci = luaM_new(pIp -> L, CallInfo);
  lua_assert(pIp -> L->ci->next == NULL);
  pIp -> L->ci->next = ci;
  ci->previous = pIp -> L->ci;
  ci->next = NULL;
  ci->u.l.trap = 0;
  pIp -> L->nci++;
  pIp -> ret = ci;
}