#include "luaS_eqlngstr.h"
void luaS_eqlngstrFun(void *p) 
{
    luaS_eqlngstr *pIp = (luaS_eqlngstr*)p;
  size_t len = pIp -> a->u.lnglen;
  lua_assert(pIp -> a->tt == LUA_VLNGSTR && pIp -> b->tt == LUA_VLNGSTR);
  return (pIp -> a == pIp -> b) ||  /* same instance or... */
    ((len == pIp -> b->u.lnglen) &&  /* equal length and ... */
     (memcmp(getlngstr(pIp -> a), getlngstr(pIp -> b), len) == 0));  /* equal contents */
}