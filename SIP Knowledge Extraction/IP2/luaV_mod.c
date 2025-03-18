#include "luaV_mod.h"
void luaV_modFun(void *p) 
{
    luaV_mod *pIp = (luaV_mod*)p;
  if (l_unlikely(l_castS2U(pIp -> n) + 1u <= 1u)) {  /* special cases: -1 or 0 */
    if (pIp -> n == 0)
      {IPCALL(luaG_runerror,ipluaG_runerror_0);}
    *(pIp -> ret) = 0;  /* pIp -> m % -1 == 0; avoid overflow with 0x80000...%-1 */
  }
  else {
    lua_Integer r = pIp -> m % pIp -> n;
    if (r != 0 && (r ^ pIp -> n) < 0)  /* 'pIp -> m/pIp -> n' would be non-integer negative? */
      r += pIp -> n;  /* correct result for different rounding */
    *(pIp -> ret) = r;
  }
}