#include "luaD_growstack.h"
void luaD_growstackFun(void *p) 
{
    luaD_growstack *pIp = (luaD_growstack*)p;
  int size = stacksize(pIp -> L);
  if (l_unlikely(size > MAXSTACK)) {
    /* if stack is larger than maximum, thread is already using the
       extra space reserved for errors, that is, thread is handling
       a stack error; cannot grow further than that. */
    lua_assert(stacksize(pIp -> L) == ERRORSTACKSIZE);
    if (pIp -> raiseerror)
      {IPCALL(luaD_throw,ipluaD_throw_0,.L = pIp->L,.errcode = LUA_ERRERR);}  /* error inside message handler */
    *(pIp -> ret) = 0; /* if not 'pIp -> raiseerror', just signal it */
  }
  else if (pIp -> n < MAXSTACK) {  /* avoids arithmetic overflows */
    int newsize = 2 * size;  /* tentative new size */
    int needed = cast_int(pIp -> L->top.p - pIp -> L->stack.p) + pIp -> n;
    if (newsize > MAXSTACK)  /* cannot cross the limit */
      newsize = MAXSTACK;
    if (newsize < needed)  /* but must respect what was asked for */
      newsize = needed;
    if (l_likely(newsize <= MAXSTACK))
      *(pIp -> ret) = luaD_reallocstack(L, newsize, raiseerror);
  }
  /* else stack overflow */
  /* add extra size to be able to handle the error message */
  {int luaD_reallocstack_ret_0;IPCALL(luaD_reallocstack,ipluaD_reallocstack_0,.L = pIp->L,.newsize = ERRORSTACKSIZE,.raiseerror = pIp->raiseerror,.ret = pIp->&luaD_reallocstack_ret_0);}
  if (pIp -> raiseerror)
    {IPCALL(luaG_runerror,ipluaG_runerror_0);}
  *(pIp -> ret) = 0;
}