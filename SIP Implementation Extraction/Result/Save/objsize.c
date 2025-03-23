#include "objsize.h"
void objsizeFun(void *p) 
{
    objsize *pIp = (objsize*)p;
  lu_mem res;
  switch ((pIp->o)->tt) {
    case LUA_VTABLE: {
      {res = luaH_size(gco2t(pIp->o));}
      break;
    }
    case LUA_VLCL: {
      LClosure cl;{cl = gco2lcl(pIp->o);}
      {res = sizeLclosure(cl->nupvalues);}
      break;
    }
    case LUA_VCCL: {
      CClosure cl;{cl = gco2ccl(pIp->o);}
      {res = sizeCclosure(cl->nupvalues);}
      break;
      break;
    }
    case LUA_VUSERDATA: {
      Udata u;{u = gco2u(pIp->o);}
      {res = sizeudata(u->nuvalue, u->len);}
      break;
    }
    case LUA_VPROTO: {
      {res = luaF_protosize(gco2p(pIp->o));}
      break;
    }
    case LUA_VTHREAD: {
      {res = luaE_threadsize(gco2th(pIp->o));}
      break;
    }
    case LUA_VSHRSTR: {
      TString ts;{ts = gco2ts(pIp->o);}
      {res = sizestrshr(cast_uint(ts->shrlen));}
      break;
    }
    case LUA_VLNGSTR: {
      TString ts;{ts = gco2ts(pIp->o);}
      {size_t luaS_sizelngstr_ret_0;IPCALL(luaS_sizelngstr,ipluaS_sizelngstr_0,.ret = &luaS_sizelngstr_ret_0);res = luaS_sizelngstr_ret_0;}
      break;
    }
    case LUA_VUPVAL: {
      res = sizeof(UpVal);
      break;
    }
    default: res = 0; {lua_assert(0);}
  }
  *(pIp->ret) =  cast(l_mem, res);
}