#include "luaS_eqlngstr.h"
void luaS_eqlngstrFun(void *p) 
{
    luaS_eqlngstr *pIp = (luaS_eqlngstr*)p;
  size_t len = (pIp->a)->u.lnglen;
  {lua_assert(pIp->a->tt == LUA_VLNGSTR && pIp->b->tt == LUA_VLNGSTR);}
  *(pIp->ret) =  (a == b) ||  /* same instance or... */
    ((len == b->u.lnglen) &&  /* equal length and ... */
     (memcmp(getlngstr(a), getlngstr(b), len) == 0));  /* equal contents */
}