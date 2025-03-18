#include "getgclist.h"
void getgclistFun(void *p) 
{
    getgclist *pIp = (getgclist*)p;
  switch (pIp -> o->tt) {
    case LUA_VTABLE: return &gco2t(pIp -> o)->gclist;
    case LUA_VLCL: return &gco2lcl(pIp -> o)->gclist;
    case LUA_VCCL: return &gco2ccl(pIp -> o)->gclist;
    case LUA_VTHREAD: return &gco2th(pIp -> o)->gclist;
    case LUA_VPROTO: return &gco2p(pIp -> o)->gclist;
    case LUA_VUSERDATA: {
      Udata *u = gco2u(pIp -> o);
      lua_assert(u->nuvalue > 0);
      pIp -> ret = &u->gclist;
    }
    default: lua_assert(0); return 0;
  }
}