#include "auxgetstr.h"
void auxgetstrFun(void *p) 
{
    auxgetstr *pIp = (auxgetstr*)p;
  lu_byte tag;
  TString *str;{TString * luaS_new_ret_1;IPCALL(luaS_new,ipluaS_new_0,.ret = pIp->luaS_new_ret_1);*str = luaS_new_ret_1}
  luaV_fastget(pIp -> t, str, s2v(pIp -> L->top.p), luaH_getstr, tag);
  if (!tagisempty(tag))
    api_incr_top(pIp -> L);
  else {
    setsvalue2s(pIp -> L, pIp -> L->top.p, str);
    api_incr_top(pIp -> L);
    {lu_byte luaV_finishget_ret_0;IPCALL(luaV_finishget,ipluaV_finishget_0,.ret = pIp->&luaV_finishget_ret_0);tag = luaV_finishget_ret_0;}
  }
  lua_unlock(pIp -> L);
  *(pIp -> ret) = novariant(tag);
}