#include "freeobj.h"
void freeobjFun(void *p) 
{
    freeobj *pIp = (freeobj*)p;
  assert_code(l_mem newmem = gettotalbytes(G(pIp -> L)) - objsize(pIp -> o));
  switch (pIp -> o->tt) {
    case LUA_VPROTO:
      {IPCALL(luaF_freeproto,ipluaF_freeproto_0);}
      break;
    case LUA_VUPVAL:
      {IPCALL(freeupval,ipfreeupval_0,.pIp->L = pIp->pIp->L,.uv = gco2upv(pIp->o));}
      break;
    case LUA_VLCL: {
      LClosure *cl = gco2lcl(pIp -> o);
      luaM_freemem(pIp -> L, cl, sizeLclosure(cl->nupvalues));
      break;
    }
    case LUA_VCCL: {
      CClosure *cl = gco2ccl(pIp -> o);
      {IPCALL(luaM_free_,ipluaM_free__1);}
      break;
    }
    case LUA_VTABLE:
      {IPCALL(luaH_free,ipluaH_free_0);}
      break;
    case LUA_VTHREAD:
      {IPCALL(luaE_freethread,ipluaE_freethread_0);}
      break;
    case LUA_VUSERDATA: {
      Udata *u = gco2u(pIp -> o);
      luaM_freemem(pIp -> L, pIp -> o, sizeudata(u->nuvalue, u->len));
      break;
    }
    case LUA_VSHRSTR: {
      TString *ts = gco2ts(pIp -> o);
      {IPCALL(luaS_remove,ipluaS_remove_0);}  /* remove it from hash table */
      luaM_freemem(pIp -> L, ts, sizestrshr(cast_uint(ts->shrlen)));
      break;
    }
    case LUA_VLNGSTR: {
      TString *ts = gco2ts(pIp -> o);
      if (ts->shrlen == LSTRMEM)  /* must free external string? */
        (*ts->falloc)(ts->ud, ts->contents, ts->u.lnglen + 1, 0);
      {IPCALL(luaM_free_,ipluaM_free__0);}
      break;
    }
    default: lua_assert(0);
  }
  lua_assert(gettotalbytes(G(pIp -> L)) == newmem);
}