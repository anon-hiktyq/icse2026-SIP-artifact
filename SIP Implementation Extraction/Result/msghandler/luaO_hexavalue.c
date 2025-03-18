#include "luaO_hexavalue.h"
void luaO_hexavalueFun(void *p) 
{
    luaO_hexavalue *pIp = (luaO_hexavalue*)p;
  lua_assert(lisxdigit(pIp -> c));
  if (lisdigit(pIp -> c)) return cast_byte(pIp -> c - '0');
  else return cast_byte((ltolower(pIp -> c) - 'a') + 10);
}