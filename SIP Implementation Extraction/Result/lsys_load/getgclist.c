#include "getgclist.h"
void getgclistFun(void *p) 
{
    getgclist *pIp = (getgclist*)p;
  switch ((pIp->o)->tt) {
    case LUA_VTABLE: pIp->ret =  &gco2t(o)->gclist;
    case LUA_VLCL: pIp->ret =  &gco2lcl(o)->gclist;
    case LUA_VCCL: pIp->ret =  &gco2ccl(o)->gclist;
    case LUA_VTHREAD: pIp->ret =  &gco2th(o)->gclist;
    case LUA_VPROTO: pIp->ret =  &gco2p(o)->gclist;
    case LUA_VUSERDATA: {
      Udata u;{u = gco2u(pIp->o);}
      {lua_assert(u->nuvalue > 0);}
      pIp->ret =  &u->gclist;
    }
    default: {lua_assert(0);} pIp->ret =  0;
  }
}