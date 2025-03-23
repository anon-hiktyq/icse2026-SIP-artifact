#include "luaV_objlen.h"
void luaV_objlenFun(void *p) 
{
    luaV_objlen *pIp = (luaV_objlen*)p;
  const TValue *tm;
  {switch (ttypetag(pIp->rb)) {
    case LUA_VTABLE: {
      Table h;{h = hvalue(pIp->rb);}
      {tm = fasttm(pIp->L, h->metatable, TM_LEN);}
      if (tm) break;  /* metamethod? break switch to call it */
      {lua_Unsigned luaH_getn_ret_0;IPCALL(luaH_getn,ipluaH_getn_0,.t = h,.ret = &luaH_getn_ret_0);setivalue(s2v(pIp->ra), l_castU2S(luaH_getn(h)));}  /* else primitive len */
      return;
    }
    case LUA_VSHRSTR: {
      {setivalue(s2v(pIp->ra), tsvalue(pIp->rb)->shrlen);}
      return;
    }
    case LUA_VLNGSTR: {
      {setivalue(s2v(pIp->ra), cast_st2S(tsvalue(pIp->rb)->u.lnglen));}
      return;
    }
    default: {  /* try metamethod */
      {const TValue * luaT_gettmbyobj_ret_0;IPCALL(luaT_gettmbyobj,ipluaT_gettmbyobj_0,.ret = luaT_gettmbyobj_ret_0);tm = luaT_gettmbyobj_ret_0;}
      {if (l_unlikely(notm(tm)))  /* no metamethod? */
        {IPCALL(luaG_typeerror,ipluaG_typeerror_0);}}
      break;
    }
  }}
  {lu_byte luaT_callTMres_ret_0;IPCALL(luaT_callTMres,ipluaT_callTMres_0,.ret = &luaT_callTMres_ret_0);luaT_callTMres_ret_0;}
}