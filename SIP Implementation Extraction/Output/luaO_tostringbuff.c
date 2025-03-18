#include "luaO_tostringbuff.h"
void luaO_tostringbuffFun(void *p) 
{
    luaO_tostringbuff *pIp = (luaO_tostringbuff*)p;
  int len;
  lua_assert(ttisnumber(pIp -> obj));
  if (ttisinteger(pIp -> obj))
    len = lua_integer2str(pIp -> buff, LUA_N2SBUFFSZ, ivalue(pIp -> obj));
  else
    len = {int tostringbuffFloat_ret_0;IPCALL(tostringbuffFloat,iptostringbuffFloat_0,.n = fltvalue(pIp->obj),.pIp->buff = pIp->pIp->buff,.pIp->ret = pIp->&tostringbuffFloat_ret_0);}
  lua_assert(len < LUA_N2SBUFFSZ);
  *(pIp -> ret) = cast_uint(len);
}