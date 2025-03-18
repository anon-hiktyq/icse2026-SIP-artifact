#include "luaT_trybinTM.h"
void luaT_trybinTMFun(void *p) 
{
    luaT_trybinTM *pIp = (luaT_trybinTM*)p;

  if (l_unlikely(callbinTM(pIp -> L, pIp -> p1, pIp -> p2, pIp -> res, pIp -> event) < 0)) {
    switch (pIp -> event) {
      case TM_BAND: case TM_BOR: case TM_BXOR:
      case TM_SHL: case TM_SHR: case TM_BNOT: {
        if (ttisnumber(pIp -> p1) && ttisnumber(pIp -> p2))
          luaG_tointerror(pIp -> L, pIp -> p1, pIp -> p2);
        else
          {IPCALL(luaG_opinterror,ipluaG_opinterror_1);}
      }
      /* calls never return, but to avoid warnings: *//* FALLTHROUGH */
      default:
        {IPCALL(luaG_opinterror,ipluaG_opinterror_0);}
    }
  }
}