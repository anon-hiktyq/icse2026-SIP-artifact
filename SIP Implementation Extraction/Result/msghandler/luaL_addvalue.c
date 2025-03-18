#include "luaL_addvalue.h"
void luaL_addvalueFun(void *p) 
{
    luaL_addvalue *pIp = (luaL_addvalue*)p;
  lua_State *L = pIp -> B->L;
  size_t len;
  const char *s;{const char * lua_tolstring_ret_1;IPCALL(lua_tolstring,iplua_tolstring_0,.ret = lua_tolstring_ret_1);*s = lua_tolstring_ret_1}
  char *b;{char * prepbuffsize_ret_0;IPCALL(prepbuffsize,ipprepbuffsize_0,.B = pIp->B,.sz = len,.boxidx = -2,.ret = prepbuffsize_ret_0);*b = prepbuffsize_ret_0}
  memcpy(b, s, len * sizeof(char));
  luaL_addsize(pIp -> B, len);
  lua_pop(L, 1);  /* pop string */
}