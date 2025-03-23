#include "luaV_idiv.h"
void luaV_idivFun(void *p) 
{
    luaV_idiv *pIp = (luaV_idiv*)p;
  {if (l_unlikely(l_castS2U(pIp->n) + 1u <= 1u)) {  /* special cases: -1 or 0 */
    if ((pIp->n) == 0)
      {IPCALL(luaG_runerror,ipluaG_runerror_0);}
    *(pIp->ret) =  intop(-, 0, m);   /* n==-1; avoid overflow with 0x80000...//-1 */
  }
  else {
    lua_Integer q = (pIp->m) / (pIp->n);  /* perform C division */
    if (((pIp->m) ^ (pIp->n)) < 0 && (pIp->m) % (pIp->n) != 0)  /* 'm/n' would be negative non-integer? */
      q -= 1;  /* correct result for different rounding */
    *(pIp->ret) =  q;
  }}
}