
#include "luaO_hexavalue.h"

/*@
  requires \valid(pIp);
  requires lisxdigit(pIp->c);
  assigns \nothing;
*/
void luaO_hexavalueFun(luaO_hexavalue *pIp) 
{
  lua_assert(lisxdigit(pIp -> c));
  if (lisdigit(pIp -> c)) return (unsigned char)(pIp -> c - '0');
  else return (unsigned char)((ltolower(pIp -> c) - 'a') + 10);
}
