#include "luaO_hexavalue.h"
void luaO_hexavalueFun(luaO_hexavalue *pIp) 
{
  lua_assert(lisxdigit(pIp -> c));
  if (lisdigit(pIp -> c)) return cast_byte(pIp -> c - '0');
  else return cast_byte((ltolower(pIp -> c) - 'a') + 10);
}