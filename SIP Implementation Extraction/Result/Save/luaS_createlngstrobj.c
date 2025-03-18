#include "luaS_createlngstrobj.h"
void luaS_createlngstrobjFun(void *p) 
{
    luaS_createlngstrobj *pIp = (luaS_createlngstrobj*)p;
  size_t totalsize;{size_t luaS_sizelngstr_ret_1;IPCALL(luaS_sizelngstr,ipluaS_sizelngstr_0,.len = l,.kind = LSTRREG,.ret = pIp->&luaS_sizelngstr_ret_1);totalsize = luaS_sizelngstr_ret_1}
  TString *ts;{TString * createstrobj_ret_0;IPCALL(createstrobj,ipcreatestrobj_0,.pIp->L = pIp->pIp->L,.totalsize = totalsize,.tag = LUA_VLNGSTR,.h = G(pIp->L)->seed,.pIp->ret = pIp->createstrobj_ret_0);*ts = createstrobj_ret_0}
  ts->u.lnglen = pIp -> l;
  ts->shrlen = LSTRREG;  /* signals that it is a regular long string */
  ts->contents = cast_charp(ts) + offsetof(TString, falloc);
  ts->contents[pIp -> l] = '\0';  /* ending 0 */
  pIp -> ret = ts;
}