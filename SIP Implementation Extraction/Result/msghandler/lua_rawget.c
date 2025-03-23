#include "lua_rawget.h"
void lua_rawgetFun(void *p) 
{
    lua_rawget *pIp = (lua_rawget*)p;
  Table *t;
  lu_byte tag;
  {lua_lock(pIp->L);}
  {api_checkpop(pIp->L, 1);}
  {Table * gettable_ret_0;IPCALL(gettable,ipgettable_0,.L = pIp->L,.idx = pIp->idx,.ret = gettable_ret_0);t = gettable_ret_0;}
  {tag = luaH_get(t, s2v(pIp->L->top.p - 1), s2v(pIp->L->top.p - 1));}
  (pIp->L)->top.p--;  /* pop key */
  int finishrawget_ret_0;IPCALL(finishrawget,ipfinishrawget_0,.L = pIp->L,.tag = tag,.ret = &finishrawget_ret_0);*(pIp->ret) =  finishrawget_ret_0;
}