#include "luaH_Hgetshortstr.h"
void luaH_HgetshortstrFun(void *p) 
{
    luaH_Hgetshortstr *pIp = (luaH_Hgetshortstr*)p;
  Node *n = hashstr(pIp -> t, pIp -> key);
  lua_assert(strisshr(pIp -> key));
  for (;;) {  /* check whether 'pIp -> key' is somewhere in the chain */
    if (keyisshrstr(n) && eqshrstr(keystrval(n), pIp -> key))
      pIp -> ret = gval(n); /* that's it */
    else {
      int nx = gnext(n);
      if (nx == 0)
        pIp -> ret = &absentkey; /* not found */
      n += nx;
    }
  }
}