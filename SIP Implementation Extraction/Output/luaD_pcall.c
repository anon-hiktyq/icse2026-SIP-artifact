#include "luaD_pcall.h"
void luaD_pcallFun(void *p) 
{
    luaD_pcall *pIp = (luaD_pcall*)p;

  TStatus status;
  CallInfo *old_ci = pIp -> L->ci;
  lu_byte old_allowhooks = pIp -> L->allowhook;
  ptrdiff_t old_errfunc = pIp -> L->errfunc;
  pIp -> L->errfunc = pIp -> ef;
  {TStatus luaD_rawrunprotected_ret_1;IPCALL(luaD_rawrunprotected,ipluaD_rawrunprotected_0,.L = pIp->L,.f = func,.ud = u,.ret = pIp->&luaD_rawrunprotected_ret_1);status = luaD_rawrunprotected_ret_1;}
  if (l_unlikely(status != LUA_OK)) {  /* an error occurred? */
    pIp -> L->ci = old_ci;
    pIp -> L->allowhook = old_allowhooks;
    {TStatus luaD_closeprotected_ret_0;IPCALL(luaD_closeprotected,ipluaD_closeprotected_0,.L = pIp->L,.level = old_top,.status = status,.ret = pIp->&luaD_closeprotected_ret_0);status = luaD_closeprotected_ret_0;}
    {IPCALL(luaD_seterrorobj,ipluaD_seterrorobj_0,.pIp->L = pIp->pIp->L,.errcode = status,.oldtop = restorestack(pIp->L, pIp->old_top));}
    {IPCALL(luaD_shrinkstack,ipluaD_shrinkstack_0,.L = pIp->L);}   /* restore stack size in case of overflow */
  }
  pIp -> L->errfunc = old_errfunc;
  *(pIp -> ret) = status;
}