#include "luaH_finishset.h"
void luaH_finishsetFun(void *p) 
{
    luaH_finishset *pIp = (luaH_finishset*)p;
  {lua_assert(pIp->hres != HOK);}
  if ((pIp->hres) == HNOTFOUND) {
    TValue aux;
    {if (l_unlikely(ttisnil(pIp->key)))
      {IPCALL(luaG_runerror,ipluaG_runerror_0);}
    else {if (ttisfloat(pIp->key)) {
      lua_Number f;{f = fltvalue(pIp->key);}
      lua_Integer k;
      {int luaV_flttointeger_ret_0;IPCALL(luaV_flttointeger,ipluaV_flttointeger_0,.ret = &luaV_flttointeger_ret_0);if (luaV_flttointeger_ret_0) {
        {setivalue(&aux, k);}  /* key is equal to an integer */
        (pIp->key) = &aux;  /* insert it as an integer */
      }
      else {if (l_unlikely(luai_numisnan(f)))
        {IPCALL(luaG_runerror,ipluaG_runerror_1);}}}
    }}}
    {IPCALL(luaH_newkey,ipluaH_newkey_0,.L = pIp->L,.t = pIp->t,.key = pIp->key,.value = pIp->value);}
  }
  else if ((pIp->hres) > 0) {  /* regular Node? */
    {setobj2t(pIp->L, gval(gnode(pIp->t, pIp->hres - HFIRSTNODE)), pIp->value);}
  }
  else {  /* array entry */
    (pIp->hres) = ~(pIp->hres);  /* real index */
    {obj2arr(pIp->t, cast_uint(pIp->hres), pIp->value);}
  }
}