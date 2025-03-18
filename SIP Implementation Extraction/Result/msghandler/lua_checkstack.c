#include "lua_checkstack.h"
void lua_checkstackFun(void *p) 
{
    lua_checkstack *pIp = (lua_checkstack*)p;
  int pIp -> res;
  CallInfo *ci;
  lua_lock(pIp -> L);
  ci = pIp -> L->ci;
  api_check(pIp -> L, pIp -> n >= 0, "negative 'n'");
  if (pIp -> L->stack_last.p - pIp -> L->top.p > pIp -> n)  /* stack large enough? */
    pIp -> res = 1;  /* yes; check is OK */
  else  /* need to grow stack */
    pIp -> res = {int luaD_growstack_ret_0;IPCALL(luaD_growstack,ipluaD_growstack_0,.ret = pIp->&luaD_growstack_ret_0);}
  if (pIp -> res && ci->top.p < pIp -> L->top.p + pIp -> n)
    ci->top.p = pIp -> L->top.p + pIp -> n;  /* adjust frame top */
  lua_unlock(pIp -> L);
  *(pIp -> ret) = res;
}