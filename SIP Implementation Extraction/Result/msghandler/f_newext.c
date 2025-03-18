#include "f_newext.h"
void f_newextFun(void *p) 
{
    f_newext *pIp = (f_newext*)p;
  struct NewExt *ne = cast(struct NewExt *, pIp -> ud);
  size_t size;{size_t luaS_sizelngstr_ret_1;IPCALL(luaS_sizelngstr,ipluaS_sizelngstr_0,.len = 0,.kind = ne->kind,.ret = &luaS_sizelngstr_ret_1);size = luaS_sizelngstr_ret_1}
  {TString * createstrobj_ret_0;IPCALL(createstrobj,ipcreatestrobj_0,.pIp->L = pIp->pIp->L,.totalsize = size,.tag = LUA_VLNGSTR,.h = G(pIp->L)->seed,.ret = createstrobj_ret_0);ne->ts = createstrobj_ret_0;}
}