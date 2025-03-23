#include "luaT_trybinTM.h"
void luaT_trybinTMFun(void *p) 
{
    luaT_trybinTM *pIp = (luaT_trybinTM*)p;
  {int callbinTM_ret_0;IPCALL(callbinTM,ipcallbinTM_0,.L = pIp->L,.p1 = pIp->p1,.p2 = pIp->p2,.res = pIp->res,.event = pIp->event,.ret = &callbinTM_ret_0);if (l_unlikely(callbinTM(pIp->L, pIp->p1, pIp->p2, pIp->res, pIp->event) < 0)) {
    switch ((pIp->event)) {
      case TM_BAND: case TM_BOR: case TM_BXOR:
      case TM_SHL: case TM_SHR: case TM_BNOT: {
        {if (ttisnumber(pIp->p1) && ttisnumber(pIp->p2))
          {IPCALL(luaG_tointerror,ipluaG_tointerror_0);}
        else
          {IPCALL(luaG_opinterror,ipluaG_opinterror_0);}}
      }
      /* calls never return, but to avoid warnings: *//* FALLTHROUGH */
      default:
        {IPCALL(luaG_opinterror,ipluaG_opinterror_1);}
    }
  }}
}