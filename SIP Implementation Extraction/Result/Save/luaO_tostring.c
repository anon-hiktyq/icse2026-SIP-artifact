#include "luaO_tostring.h"
void luaO_tostringFun(void *p) 
{
    luaO_tostring *pIp = (luaO_tostring*)p;
  char buff[LUA_N2SBUFFSZ];
  unsigned len;{unsigned int luaO_tostringbuff_ret_0;IPCALL(luaO_tostringbuff,ipluaO_tostringbuff_0,.obj = pIp->obj,.buff = buff,.ret = &luaO_tostringbuff_ret_0);len = luaO_tostringbuff_ret_0}
  setsvalue(pIp -> L, pIp -> obj, luaS_newlstr(pIp -> L, buff, len));
}