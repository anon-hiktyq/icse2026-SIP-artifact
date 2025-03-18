#include "lua_gc.h"
void lua_gcFun(void *p) 
{
    lua_gc *pIp = (lua_gc*)p;
  va_list argp;
  int res = 0;
  global_State *g = G(pIp -> L);
  if (g->gcstp & (GCSTPGC | GCSTPCLS))  /* internal stop? */
    *(pIp -> ret) = -1; /* all options are invalid when stopped */
  lua_lock(pIp -> L);
  va_start(argp, pIp -> what);
  switch (pIp -> what) {
    case LUA_GCSTOP: {
      g->gcstp = GCSTPUSR;  /* stopped by the user */
      break;
    }
    case LUA_GCRESTART: {
      {IPCALL(luaE_setdebt,ipluaE_setdebt_1);}
      g->gcstp = 0;  /* (other bits must be zero here) */
      break;
    }
    case LUA_GCCOLLECT: {
      {IPCALL(luaC_fullgc,ipluaC_fullgc_0);}
      break;
    }
    case LUA_GCCOUNT: {
      /* GC values are expressed in Kbytes: #bytes/2^10 */
      res = cast_int(gettotalbytes(g) >> 10);
      break;
    }
    case LUA_GCCOUNTB: {
      res = cast_int(gettotalbytes(g) & 0x3ff);
      break;
    }
    case LUA_GCSTEP: {
      lu_byte oldstp = g->gcstp;
      l_mem n = cast(l_mem, va_arg(argp, size_t));
      int work = 0;  /* true if GC did some work */
      g->gcstp = 0;  /* allow GC to run (other bits must be zero here) */
      if (n <= 0)
        n = g->GCdebt;  /* force to run one basic step */
      {IPCALL(luaE_setdebt,ipluaE_setdebt_0);}
      luaC_condGC(pIp -> L, (void)0, work = 1);
      if (work && g->gcstate == GCSpause)  /* end of cycle? */
        res = 1;  /* signal it */
      g->gcstp = oldstp;  /* restore previous state */
      break;
    }
    case LUA_GCISRUNNING: {
      res = gcrunning(g);
      break;
    }
    case LUA_GCGEN: {
      res = (g->gckind == KGC_INC) ? LUA_GCINC : LUA_GCGEN;
      {IPCALL(luaC_changemode,ipluaC_changemode_1);}
      break;
    }
    case LUA_GCINC: {
      res = (g->gckind == KGC_INC) ? LUA_GCINC : LUA_GCGEN;
      {IPCALL(luaC_changemode,ipluaC_changemode_0);}
      break;
    }
    case LUA_GCPARAM: {
      int param = va_arg(argp, int);
      int value = va_arg(argp, int);
      api_check(pIp -> L, 0 <= param && param < LUA_GCPN, "invalid parameter");
      res = cast_int(luaO_applyparam(g->gcparams[param], 100));
      if (value >= 0)
        g->gcparams[param] = {lu_byte luaO_codeparam_ret_0;IPCALL(luaO_codeparam,ipluaO_codeparam_0,.ret = pIp->&luaO_codeparam_ret_0);}
      break;
    }
    default: res = -1;  /* invalid option */
  }
  va_end(argp);
  lua_unlock(pIp -> L);
  *(pIp -> ret) = res;
}