#include "luaS_hashlongstr.h"
void luaS_hashlongstrFun(void *p) 
{
    luaS_hashlongstr *pIp = (luaS_hashlongstr*)p;
  {lua_assert(pIp->ts->tt == LUA_VLNGSTR);}
  if ((pIp->ts)->extra == 0) {  /* no hash? */
    size_t len = (pIp->ts)->u.lnglen;
    {pIp->ts->hash = luaS_hash(getlngstr(pIp->ts), len, pIp->ts->hash);}
    (pIp->ts)->extra = 1;  /* now it has its hash */
  }
  *(pIp->ret) =  (pIp->ts)->hash;
}