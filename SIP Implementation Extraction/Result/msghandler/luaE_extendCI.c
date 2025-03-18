#include "luaE_extendCI.h"
void luaE_extendCIFun(void *p) 
{
    luaE_extendCI *pIp = (luaE_extendCI*)p;
  CallInfo pIp -> *ci;
  lua_assert(pIp -> L->pIp -> ci->next == NULL);
  pIp -> ci = luaM_new(pIp -> L, CallInfo);
  lua_assert(pIp -> L->pIp -> ci->next == NULL);
  pIp -> L->pIp -> ci->next = pIp -> ci;
  pIp -> ci->previous = pIp -> L->pIp -> ci;
  pIp -> ci->next = NULL;
  pIp -> ci->u.l.trap = 0;
  pIp -> L->nci++;
  pIp -> ret = ci;
}