#include "luaH_get.h"
void luaH_getFun(void *p) 
{
    luaH_get *pIp = (luaH_get*)p;
  const TValue *slot;
  switch (ttypetag(pIp -> key)) {
    case LUA_VSHRSTR:
      slot = {const TValue * luaH_Hgetshortstr_ret_4;IPCALL(luaH_Hgetshortstr,ipluaH_Hgetshortstr_0,.pIp->t = pIp->pIp->t,.pIp->key = pIp->tsvalue(pIp->key),.pIp->ret = pIp->luaH_Hgetshortstr_ret_4);}
      break;
    case LUA_VNUMINT:
      *(pIp -{lu_byte luaH_getint_ret_3;IPCALL(luaH_getint,ipluaH_getint_1,.pIp->t = pIp->pIp->t,.pIp->key = pIp->ivalue(pIp->key),.pIp->res = pIp->pIp->res,.pIp->ret = pIp->&luaH_getint_ret_3);}y), res);
    case LUA_VNIL:
      slot = &absentkey;
      break;
    case LUA_VNUMFLT: {
      lua_Integer k;
      {int luaV_flttointeger_ret_2;IPCALL(luaV_flttointeger,ipluaV_flttointeger_0,.ret = pIp->&luaV_flttointeger_ret_2);if ((luaV_flttointeger_ret_2) /* integral index? */
        *(pIp -{lu_byte luaH_getint_r}t_1;IPCALL(luaH_getint,ipluaH_getint_0,.t = pIp->t,.key = pIp->k,.res = pIp->res,.ret = pIp->&luaH_getint_ret_1);} k, res); /* use specialized version */
      /* else... */
    }  /* FALLTHROUGH */
    default:
      slot = {const TValue * getgeneric_ret_0;IPCALL(getgeneric,ipgetgeneric_0,.t = pIp->t,.key = pIp->key,.deadok = 0,.ret = pIp->getgeneric_ret_0);}
      break;
  }
  *(pIp -> ret) = finishnodeget(slot, res);
}