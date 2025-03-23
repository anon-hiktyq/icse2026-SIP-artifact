#include "luaO_hexavalue.h"
void luaO_hexavalueFun(void *p) 
{
    luaO_hexavalue *pIp = (luaO_hexavalue*)p;
  {lua_assert(lisxdigit(pIp->c));}
  {if (lisdigit(pIp->c)) *(pIp->ret) =  cast_byte(c - '0');
  else *(pIp->ret) =  cast_byte((ltolower(c) - 'a') + 10);}
}