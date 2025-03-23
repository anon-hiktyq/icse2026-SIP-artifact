#include "mainpositionTV.h"
void mainpositionTVFun(void *p) 
{
    mainpositionTV *pIp = (mainpositionTV*)p;
  {switch (ttypetag(pIp->key)) {
    case LUA_VNUMINT: {
      lua_Integer i;{i = ivalue(pIp->key);}
      Node * hashint_ret_0;IPCALL(hashint,iphashint_0,.t = pIp->t,.i = i,.ret = hashint_ret_0);pIp->ret =  hashint_ret_0;
    }
    case LUA_VNUMFLT: {
      lua_Number n;{n = fltvalue(pIp->key);}
      unsigned int l_hashfloat_ret_0;IPCALL(l_hashfloat,ipl_hashfloat_0,.n = n,.ret = &l_hashfloat_ret_0);pIp->ret =  hashmod(t, l_hashfloat(n));
    }
    case LUA_VSHRSTR: {
      TString ts;{ts = tsvalue(pIp->key);}
      pIp->ret =  hashstr(t, ts);
    }
    case LUA_VLNGSTR: {
      TString ts;{ts = tsvalue(pIp->key);}
      unsigned int luaS_hashlongstr_ret_0;IPCALL(luaS_hashlongstr,ipluaS_hashlongstr_0,.ts = ts,.ret = &luaS_hashlongstr_ret_0);pIp->ret =  hashpow2(t, luaS_hashlongstr(ts));
    }
    case LUA_VFALSE:
      pIp->ret =  hashboolean(t, 0);
    case LUA_VTRUE:
      pIp->ret =  hashboolean(t, 1);
    case LUA_VLIGHTUSERDATA: {
      void p;{p = pvalue(pIp->key);}
      pIp->ret =  hashpointer(t, p);
    }
    case LUA_VLCF: {
      lua_CFunction f;{f = fvalue(pIp->key);}
      pIp->ret =  hashpointer(t, f);
    }
    default: {
      GCObject o;{o = gcvalue(pIp->key);}
      pIp->ret =  hashpointer(t, o);
    }
  }}
}