#include "objsize.h"
void objsizeFun(void *p) 
{
    objsize *pIp = (objsize*)p;
  lu_mem res;
  switch (pIp -> o->tt) {
    case LUA_VTABLE: {
      {lu_mem luaH_size_ret_3;IPCALL(luaH_size,ipluaH_size_0,.ret = pIp->&luaH_size_ret_3);res = luaH_size_ret_3;}
      break;
    }
    case LUA_VLCL: {
      LClosure *cl = gco2lcl(pIp -> o);
      res = sizeLclosure(cl->nupvalues);
      break;
    }
    case LUA_VCCL: {
      CClosure *cl = gco2ccl(pIp -> o);
      res = sizeCclosure(cl->nupvalues);
      break;
      break;
    }
    case LUA_VUSERDATA: {
      Udata *u = gco2u(pIp -> o);
      res = sizeudata(u->nuvalue, u->len);
      break;
    }
    case LUA_VPROTO: {
      {lu_mem luaF_protosize_ret_2;IPCALL(luaF_protosize,ipluaF_protosize_0,.ret = pIp->&luaF_protosize_ret_2);res = luaF_protosize_ret_2;}
      break;
    }
    case LUA_VTHREAD: {
      {lu_mem luaE_threadsize_ret_1;IPCALL(luaE_threadsize,ipluaE_threadsize_0,.ret = pIp->&luaE_threadsize_ret_1);res = luaE_threadsize_ret_1;}
      break;
    }
    case LUA_VSHRSTR: {
      TString *ts = gco2ts(pIp -> o);
      res = sizestrshr(cast_uint(ts->shrlen));
      break;
    }
    case LUA_VLNGSTR: {
      TString *ts = gco2ts(pIp -> o);
      {size_t luaS_sizelngstr_ret_0;IPCALL(luaS_sizelngstr,ipluaS_sizelngstr_0,.ret = pIp->&luaS_sizelngstr_ret_0);res = luaS_sizelngstr_ret_0;}
      break;
    }
    case LUA_VUPVAL: {
      res = sizeof(UpVal);
      break;
    }
    default: res = 0; lua_assert(0);
  }
  *(pIp -> ret) = cast(l_mem, res);
}