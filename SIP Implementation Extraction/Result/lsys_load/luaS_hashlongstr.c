#include "luaS_hashlongstr.h"
void luaS_hashlongstrFun(void *p) 
{
    luaS_hashlongstr *pIp = (luaS_hashlongstr*)p;
  lua_assert(pIp -> ts->tt == LUA_VLNGSTR);
  if (pIp -> ts->extra == 0) {  /* no hash? */
    size_t len = pIp -> ts->u.lnglen;
    {unsigned int luaS_hash_ret_0;IPCALL(luaS_hash,ipluaS_hash_0,.str = getlngstr(pIp->ts),.l = len,.seed = pIp->ts->hash,.pIp->ret = pIp->&luaS_hash_ret_0);pIp->ts->hash = luaS_hash_ret_0;}
    pIp -> ts->extra = 1;  /* now it has its hash */
  }
  *(pIp -> ret) = ts->hash;
}