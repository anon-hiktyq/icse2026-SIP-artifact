#include "f_newext.h"
void f_newextFun(void *p) 
{
    f_newext *pIp = (f_newext*)p;
  struct NewExt ne;{ne = cast(struct NewExt *, pIp->ud);}
  size_t size;{size_t luaS_sizelngstr_ret_0; IPCALL(luaS_sizelngstr,ipluaS_sizelngstr_0,.len = 0,.kind = ne->kind,.ret = &luaS_sizelngstr_ret_0);size = luaS_sizelngstr_ret_0;}
  {ne->ts = createstrobj(pIp->L, size, LUA_VLNGSTR, G(pIp->L)->seed);}
}