#include "freeobj.h"
void freeobjFun(void *p) 
{
    freeobj *pIp = (freeobj*)p;
  newmem;{newmem = gettotalbytes(G(pIp->L)) - objsize(pIp->o);}
  switch ((pIp->o)->tt) {
    case LUA_VPROTO:
      {luaF_freeproto(pIp->L, gco2p(pIp->o));}
      break;
    case LUA_VUPVAL:
      {freeupval(pIp->L, gco2upv(pIp->o));}
      break;
    case LUA_VLCL: {
      LClosure cl;{cl = gco2lcl(pIp->o);}
      {luaM_freemem(pIp->L, cl, sizeLclosure(cl->nupvalues));}
      break;
    }
    case LUA_VCCL: {
      CClosure cl;{cl = gco2ccl(pIp->o);}
      {luaM_freemem(pIp->L, cl, sizeCclosure(cl->nupvalues));}
      break;
    }
    case LUA_VTABLE:
      {luaH_free(pIp->L, gco2t(pIp->o));}
      break;
    case LUA_VTHREAD:
      {luaE_freethread(pIp->L, gco2th(pIp->o));}
      break;
    case LUA_VUSERDATA: {
      Udata u;{u = gco2u(pIp->o);}
      {luaM_freemem(pIp->L, pIp->o, sizeudata(u->nuvalue, u->len));}
      break;
    }
    case LUA_VSHRSTR: {
      TString ts;{ts = gco2ts(pIp->o);}
      {IPCALL(luaS_remove,ipluaS_remove_0);}  /* remove it from hash table */
      {luaM_freemem(pIp->L, ts, sizestrshr(cast_uint(ts->shrlen)));}
      break;
    }
    case LUA_VLNGSTR: {
      TString ts;{ts = gco2ts(pIp->o);}
      if (ts->shrlen == LSTRMEM)  /* must free external string? */
        (*ts->falloc)(ts->ud, ts->contents, ts->u.lnglen + 1, 0);
      {size_t luaS_sizelngstr_ret_0;IPCALL(luaS_sizelngstr,ipluaS_sizelngstr_0,.len = ts->u.lnglen,.kind = ts->shrlen,.ret = &luaS_sizelngstr_ret_0);luaM_freemem(pIp->L, ts, luaS_sizelngstr(ts->u.lnglen, ts->shrlen));}
      break;
    }
    default: {lua_assert(0);}
  }
  {lua_assert(gettotalbytes(G(pIp->L)) == newmem);}
}