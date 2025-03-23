#include "luaD_shrinkstack.h"
void luaD_shrinkstackFun(void *p) 
{
    luaD_shrinkstack *pIp = (luaD_shrinkstack*)p;
  int inuse;{int stackinuse_ret_0; IPCALL(stackinuse,ipstackinuse_0,.L = pIp->L,.ret = &stackinuse_ret_0);inuse = stackinuse_ret_0;}
  int max = (inuse > MAXSTACK / 3) ? MAXSTACK : inuse * 3;
  /* if thread is currently not handling a stack overflow and its
     size is larger than maximum "reasonable" size, shrink it */
  {if (inuse <= MAXSTACK && stacksize(pIp->L) > max) {
    int nsize = (inuse > MAXSTACK / 2) ? MAXSTACK : inuse * 2;
    {int luaD_reallocstack_ret_0;IPCALL(luaD_reallocstack,ipluaD_reallocstack_0,.L = pIp->L,.newsize = nsize,.raiseerror = 0,.ret = &luaD_reallocstack_ret_0);luaD_reallocstack_ret_0;}  /* ok if that fails */
  }
  else  /* don't change stack */
    {condmovestack(pIp->L,(void)0,(void)0);}}  /* (change only for debugging) */
  {IPCALL(luaE_shrinkCI,ipluaE_shrinkCI_0);}  /* shrink CI list */
}