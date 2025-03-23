#include "luaG_addinfo.h"
void luaG_addinfoFun(void *p) 
{
    luaG_addinfo *pIp = (luaG_addinfo*)p;
  char buff[LUA_IDSIZE];
  if ((pIp->src)) {
    size_t idlen;
    const char id;{id = getlstr(pIp->src, idlen);}
    {IPCALL(luaO_chunkid,ipluaO_chunkid_0);}
  }
  else {  /* no source available; use "?" instead */
    buff[0] = '?'; buff[1] = '\0';
  }
  const char * luaO_pushfstring_ret_0;IPCALL(luaO_pushfstring,ipluaO_pushfstring_0,.ret = luaO_pushfstring_ret_0);pIp->ret =  luaO_pushfstring_ret_0;
}