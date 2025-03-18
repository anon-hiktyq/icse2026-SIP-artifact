#include "luaH_pset.h"
void luaH_psetFun(void *p) 
{
    luaH_pset *pIp = (luaH_pset*)p;
  switch (ttypetag(pIp -> key)) {
    case LUA_VSHRSTR: return {int luaH_psetshortstr_ret_4;IPCALL(luaH_psetshortstr,ipluaH_psetshortstr_0,.pIp->t = pIp->pIp->t,.pIp->key = pIp->tsvalue(pIp->key),.pIp->val = pIp->pIp->val,.pIp->ret = pIp->&luaH_psetshortstr_ret_4);}
    case LUA_VNUMINT: return {int psetint_ret_3;IPCALL(psetint,ippsetint_1,.pIp->t = pIp->pIp->t,.pIp->key = pIp->ivalue(pIp->key),.pIp->val = pIp->pIp->val,.pIp->ret = pIp->&psetint_ret_3);}
    case LUA_VNIL: return HNOTFOUND;
    case LUA_VNUMFLT: {
      lua_Integer k;
      {int luaV_flttointeger_ret_2;IPCALL(luaV_flttointeger,ipluaV_flttointeger_0,.ret = pIp->&luaV_flttointeger_ret_2);if ((luaV_flttointeger_ret_2) /* integral index? */
        *(pIp -{int psetint_ret_1}IPCALL(psetint,ippsetint_0,.t = pIp->t,.key = pIp->k,.val = pIp->val,.ret = pIp->&psetint_ret_1);} k, val); /* use specialized version */
      /* else... */
    }  /* FALLTHROUGH */
    default:
      *(pIp -{const TValue * getgeneric_ret_0;IPCALL(getgeneric,ipgetgeneric_0,.t = pIp->t,.key = pIp->key,.deadok = 0,.ret = pIp->getgeneric_ret_0);int finishnodeset_ret_0;IPCALL(finishnodeset,ipfinishnodeset_0,.t = pIp->t,.slot = getgeneric_ret_0,.val = pIp->val,.ret = pIp->&finishnodeset_ret_0);}0), val);
  }
}