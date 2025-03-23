#include "luaH_pset.h"
void luaH_psetFun(void *p) 
{
    luaH_pset *pIp = (luaH_pset*)p;
  {switch (ttypetag(pIp->key)) {
    case LUA_VSHRSTR: *(pIp->ret) =  luaH_psetshortstr(t, tsvalue(key), val);
    case LUA_VNUMINT: *(pIp->ret) =  psetint(t, ivalue(key), val);
    case LUA_VNIL: *(pIp->ret) =  HNOTFOUND;
    case LUA_VNUMFLT: {
      lua_Integer k;
      {if (luaV_flttointeger(fltvalue(pIp->key), &k, F2Ieq)) /* integral index? */
        int psetint_ret_0;IPCALL(psetint,ippsetint_0,.t = pIp->t,.key = k,.val = pIp->val,.ret = &psetint_ret_0);*(pIp->ret) =  psetint_ret_0; } /* use specialized version */
      /* else... */
    }  /* FALLTHROUGH */
    default:
      const TValue * getgeneric_ret_0;IPCALL(getgeneric,ipgetgeneric_0,.t = pIp->t,.key = pIp->key,.deadok = 0,.ret = getgeneric_ret_0);int finishnodeset_ret_0;IPCALL(finishnodeset,ipfinishnodeset_0,.t = pIp->t,.slot = getgeneric_ret_0,.val = pIp->val,.ret = &finishnodeset_ret_0);*(pIp->ret) =  finishnodeset_ret_0;
  }}
}