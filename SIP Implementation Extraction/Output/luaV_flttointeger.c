#include "luaV_flttointeger.h"
void luaV_flttointegerFun(void *p) 
{
    luaV_flttointeger *pIp = (luaV_flttointeger*)p;
  lua_Number f = l_floor(pIp -> n);
  if (pIp -> n != f) {  /* not an integral value? */
    if (pIp -> mode == F2Ieq) return 0;  /* fails if pIp -> mode demands integral value */
    else if (pIp -> mode == F2Iceil)  /* needs ceiling? */
      f += 1;  /* convert floor to ceiling (remember: pIp -> n != f) */
  }
  *(pIp -> ret) = lua_numbertointeger(f, p);
}