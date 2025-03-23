#include "addnum2buff.h"
void addnum2buffFun(void *p) 
{
    addnum2buff *pIp = (addnum2buff*)p;
  char numbuff[LUA_N2SBUFFSZ];
  unsigned len;{unsigned int luaO_tostringbuff_ret_0; IPCALL(luaO_tostringbuff,ipluaO_tostringbuff_0,.obj = pIp->num,.buff = numbuff,.ret = &luaO_tostringbuff_ret_0);len = luaO_tostringbuff_ret_0;}
  {IPCALL(addstr2buff,ipaddstr2buff_0,.buff = pIp->buff,.str = numbuff,.slen = len);}
}