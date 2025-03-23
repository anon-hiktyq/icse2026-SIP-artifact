#include "luaH_get.h"
void luaH_getFun(void *p) 
{
    luaH_get *pIp = (luaH_get*)p;
  const TValue *slot;
  {switch (ttypetag(pIp->key)) {
    case LUA_VSHRSTR:
      {slot = luaH_Hgetshortstr(pIp->t, tsvalue(pIp->key));}
      break;
    case LUA_VNUMINT:
      *(pIp->ret) =  luaH_getint(t, ivalue(key), res);
    case LUA_VNIL:
      slot = &absentkey;
      break;
    case LUA_VNUMFLT: {
      lua_Integer k;
      {if (luaV_flttointeger(fltvalue(pIp->key), &k, F2Ieq)) /* integral index? */
        lu_byte luaH_getint_ret_0;IPCALL(luaH_getint,ipluaH_getint_0,.t = pIp->t,.key = k,.res = pIp->res,.ret = &luaH_getint_ret_0);*(pIp->ret) =  luaH_getint_ret_0; } /* use specialized version */
      /* else... */
    }  /* FALLTHROUGH */
    default:
      {const TValue * getgeneric_ret_0;IPCALL(getgeneric,ipgetgeneric_0,.t = pIp->t,.key = pIp->key,.deadok = 0,.ret = getgeneric_ret_0);slot = getgeneric_ret_0;}
      break;
  }}
  lu_byte finishnodeget_ret_0;IPCALL(finishnodeget,ipfinishnodeget_0,.val = slot,.res = pIp->res,.ret = &finishnodeget_ret_0);*(pIp->ret) =  finishnodeget_ret_0;
}