#include "forlimit.h"
void forlimitFun(void *p) 
{
    forlimit *pIp = (forlimit*)p;

  {int luaV_tointeger_ret_0;IPCALL(luaV_tointeger,ipluaV_tointeger_0,.obj = pIp->lim,.pIp->p = pIp->pIp->p,.mode = (pIp->step < 0 ? F2Iceil : F2Ifloor),.pIp->ret = pIp->&luaV_tointeger_ret_0);if (!(luaV_tointeger_ret_0) {
    /* not coercible to in integer */
    lua_Number flim;  /* try to convert to float */
    if (!tonumber(pIp -> lim, &flim)) /* cannot convert to float? */
      {IPCALL(luaG_forerror,ipluaG_forerror_0);}
    /* else 'flim' is a float out of integer bounds */
    if (luai_numlt(0, flim)) {  /* if it is positive, it is too large */
      if (pIp -> step < 0) return 1;  /* initial value must be less than it */
      pIp -> *p = LUA_MAXINTEGER;  /* truncate */
    }
    else {  /* it is less than min integer */
      if (pIp -> step > 0) return 1;  /* initial value must be greater than it */
      pIp -> *p = LUA_MININTEGER;  /* truncate */
    }
  }}
  *(pIp -> ret) = (step > 0 ? init > *p : init < *p); /* not to run? */
}