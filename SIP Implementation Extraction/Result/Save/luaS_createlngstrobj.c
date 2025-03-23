#include "luaS_createlngstrobj.h"
void luaS_createlngstrobjFun(void *p) 
{
    luaS_createlngstrobj *pIp = (luaS_createlngstrobj*)p;
  size_t totalsize;{size_t luaS_sizelngstr_ret_0; IPCALL(luaS_sizelngstr,ipluaS_sizelngstr_0,.len = pIp->l,.kind = LSTRREG,.ret = &luaS_sizelngstr_ret_0);totalsize = luaS_sizelngstr_ret_0;}
  TString ts;{ts = createstrobj(pIp->L, totalsize, LUA_VLNGSTR, G(pIp->L)->seed);}
  ts->u.lnglen = (pIp->l);
  ts->shrlen = LSTRREG;  /* signals that it is a regular long string */
  {ts->contents = cast_charp(ts) + offsetof(TString, falloc);}
  ts->contents[(pIp->l)] = '\0';  /* ending 0 */
  pIp->ret =  ts;
}