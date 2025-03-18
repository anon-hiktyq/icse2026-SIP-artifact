#include "luaD_closeprotected.h"
void luaD_closeprotectedFun(void *p) 
{
    luaD_closeprotected *pIp = (luaD_closeprotected*)p;
  CallInfo *old_ci = pIp -> L->ci;
  lu_byte old_allowhooks = pIp -> L->allowhook;
  for (;;) {  /* keep closing upvalues until no more errors */
    struct CloseP pcl;
    pcl.pIp -> level = restorestack(pIp -> L, pIp -> level); pcl.pIp -> status = pIp -> status;
    {TStatus luaD_rawrunprotected_ret_0;IPCALL(luaD_rawrunprotected,ipluaD_rawrunprotected_0,.L = pIp->L,.f = &closepaux,.ud = &pcl,.ret = pIp->&luaD_rawrunprotected_ret_0);pIp->status = luaD_rawrunprotected_ret_0;}
    if (l_likely(pIp -> status == LUA_OK))  /* no more errors? */
      *(pIp -> ret) = pcl.status;
    else {  /* an error occurred; restore saved state and repeat */
      pIp -> L->ci = old_ci;
      pIp -> L->allowhook = old_allowhooks;
    }
  }
}