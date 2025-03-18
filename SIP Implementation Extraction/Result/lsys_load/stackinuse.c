#include "stackinuse.h"
void stackinuseFun(void *p) 
{
    stackinuse *pIp = (stackinuse*)p;
  CallInfo *ci;
  int pIp -> res;
  StkId lim = pIp -> L->top.p;
  for (ci = pIp -> L->ci; ci != NULL; ci = ci->previous) {
    if (lim < ci->top.p) lim = ci->top.p;
  }
  lua_assert(lim <= pIp -> L->stack_last.p + EXTRA_STACK);
  pIp -> res = cast_int(lim - pIp -> L->stack.p) + 1;  /* part of stack in use */
  if (pIp -> res < LUA_MINSTACK)
    pIp -> res = LUA_MINSTACK;  /* ensure a minimum size */
  *(pIp -> ret) = res;
}