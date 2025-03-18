#include "mainpositionTV.h"
void mainpositionTVFun(void *p) 
{
    mainpositionTV *pIp = (mainpositionTV*)p;
  switch (ttypetag(pIp -> key)) {
    case LUA_VNUMINT: {
      lua_Integer i = ivalue(pIp -> key);
      pIp -> ret = hashint(t, i);
    }
    case LUA_VNUMFLT: {
      lua_Number n = fltvalue(pIp -> key);
      pIp -> ret = hashmod(t, l_hashfloat(n));
    }
    case LUA_VSHRSTR: {
      TString *ts = tsvalue(pIp -> key);
      pIp -> ret = hashstr(t, ts);
    }
    case LUA_VLNGSTR: {
      TString *ts = tsvalue(pIp -> key);
      pIp -> ret = hashpow2(t, luaS_hashlongstr(ts));
    }
    case LUA_VFALSE:
      pIp -> ret = hashboolean(t, 0);
    case LUA_VTRUE:
      pIp -> ret = hashboolean(t, 1);
    case LUA_VLIGHTUSERDATA: {
      void *p = pvalue(pIp -> key);
      pIp -> ret = hashpointer(t, p);
    }
    case LUA_VLCF: {
      lua_CFunction f = fvalue(pIp -> key);
      pIp -> ret = hashpointer(t, f);
    }
    default: {
      GCObject *o = gcvalue(pIp -> key);
      pIp -> ret = hashpointer(t, o);
    }
  }
}