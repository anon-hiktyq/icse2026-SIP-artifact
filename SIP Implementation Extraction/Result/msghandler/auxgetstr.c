#include "auxgetstr.h"
void auxgetstrFun(void *p) 
{
    auxgetstr *pIp = (auxgetstr*)p;
  lu_byte tag;
  TString str;{TString * luaS_new_ret_0; IPCALL(luaS_new,ipluaS_new_0,.ret = luaS_new_ret_0);str = luaS_new_ret_0;}
  {luaV_fastget(pIp->t, str, s2v(pIp->L->top.p), luaH_getstr, tag);}
  {if (!tagisempty(tag))
    {api_incr_top(pIp->L);}
  else {
    {setsvalue2s(pIp->L, pIp->L->top.p, str);}
    {api_incr_top(pIp->L);}
    {tag = luaV_finishget(pIp->L, pIp->t, s2v(pIp->L->top.p - 1), pIp->L->top.p - 1, tag);}
  }}
  {lua_unlock(pIp->L);}
  *(pIp->ret) =  novariant(tag);
}