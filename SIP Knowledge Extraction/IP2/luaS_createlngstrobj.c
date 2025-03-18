#include "luaS_createlngstrobj.h"
void luaS_createlngstrobjFun(void *p) 
{
    luaS_createlngstrobj *pIp = (luaS_createlngstrobj*)p;
  size_t totalsize;{size_t luaS_sizelngstr_ret_1;IPCALL(luaS_sizelngstr,ipluaS_sizelngstr_0,.len = l,.kind = LSTRREG,.ret = pIp->&luaS_sizelngstr_ret_1);totalsize = luaS_sizelngstr_ret_1}
  TString *pIp->ts;{TString * createstrobj_ret_0;IPCALL(createstrobj,ipcreatestrobj_0,.pIp->L = pIp->pIp->L,.totalsize = totalsize,.tag = LUA_VLNGSTR,.h = G(pIp->L)->seed,.pIp->ret = pIp->createstrobj_ret_0);*pIp->ts = createstrobj_ret_0}
  pIp -> ts->u.lnglen = pIp -> l;
  pIp -> ts->shrlen = LSTRREG;  /* signals that it is a regular long string */
  pIp -> ts->contents = cast_charp(pIp -> ts) + offsetof(TString, falloc);
  pIp -> ts->contents[pIp -> l] = '\0';  /* ending 0 */
  pIp -> ret = ts;
}