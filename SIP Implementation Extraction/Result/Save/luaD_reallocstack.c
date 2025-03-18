#include "luaD_reallocstack.h"
void luaD_reallocstackFun(void *p) 
{
    luaD_reallocstack *pIp = (luaD_reallocstack*)p;
  int oldsize = stacksize(pIp -> L);
  int i;
  StkId newstack;
  StkId oldstack = pIp -> L->stack.p;
  lu_byte oldgcstop = G(pIp -> L)->gcstopem;
  lua_assert(pIp -> newsize <= MAXSTACK || pIp -> newsize == ERRORSTACKSIZE);
  {IPCALL(relstack,iprelstack_0,.L = pIp->L);}  /* change pointers to offsets */
  G(pIp -> L)->gcstopem = 1;  /* stop emergency collection */
  newstack = luaM_reallocvector(pIp -> L, oldstack, oldsize + EXTRA_STACK,
                                   pIp -> newsize + EXTRA_STACK, StackValue);
  G(pIp -> L)->gcstopem = oldgcstop;  /* restore emergency collection */
  if (l_unlikely(newstack == NULL)) {  /* reallocation failed? */
    {IPCALL(correctstack,ipcorrectstack_1,.L = pIp->L,.oldstack = oldstack);}  /* change offsets back to pointers */
    if (pIp -> raiseerror)
      luaM_error(pIp -> L);
    else return 0;  /* do not raise an error */
  }
  pIp -> L->stack.p = newstack;
  {IPCALL(correctstack,ipcorrectstack_0,.L = pIp->L,.oldstack = oldstack);}  /* change offsets back to pointers */
  pIp -> L->stack_last.p = pIp -> L->stack.p + pIp -> newsize;
  for (i = oldsize + EXTRA_STACK; i < pIp -> newsize + EXTRA_STACK; i++)
    setnilvalue(s2v(newstack + i)); /* erase new segment */
  *(pIp -> ret) = 1;
}