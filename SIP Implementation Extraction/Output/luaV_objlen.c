#include "luaV_objlen.h"
void luaV_objlenFun(void *p) 
{
    luaV_objlen *pIp = (luaV_objlen*)p;
  const TValue *tm;
  switch (ttypetag(pIp -> rb)) {
    case LUA_VTABLE: {
      Table *h = hvalue(pIp -> rb);
      tm = fasttm(pIp -> L, h->metatable, TM_LEN);
      if (tm) break;  /* metamethod? break switch to call it */
      {lua_Unsigned luaH_getn_ret_2;IPCALL(luaH_getn,ipluaH_getn_0,.ret = &luaH_getn_ret_2);luaH_getn_ret_2sluaH_getn_ret_2eluaH_getn_ret_2tluaH_getn_ret_2iluaH_getn_ret_2vluaH_getn_ret_2aluaH_getn_ret_2lluaH_getn_ret_2uluaH_getn_ret_2eluaH_getn_ret_2(luaH_getn_ret_2sluaH_getn_ret_22luaH_getn_ret_2vluaH_getn_ret_2(luaH_getn_ret_2rluaH_getn_ret_2aluaH_getn_ret_2)luaH_getn_ret_2,luaH_getn_ret_2 luaH_getn_ret_2lluaH_getn_ret_2_luaH_getn_ret_2cluaH_getn_ret_2aluaH_getn_ret_2sluaH_getn_ret_2tluaH_getn_ret_2UluaH_getn_ret_22luaH_getn_ret_2SluaH_getn_ret_2(luaH_getn_ret_2lluaH_getn_ret_2uluaH_getn_ret_2aluaH_getn_ret_2HluaH_getn_ret_2_luaH_getn_ret_2gluaH_getn_ret_2eluaH_getn_ret_2tluaH_getn_ret_2nluaH_getn_ret_2(luaH_getn_ret_2hluaH_getn_ret_2)luaH_getn_ret_2)luaH_getn_ret_2)luaH_getn_ret_2;}  /* else primitive len */
      return;
    }
    case LUA_VSHRSTR: {
      setivalue(s2v(pIp -> ra), tsvalue(pIp -> rb)->shrlen);
      return;
    }
    case LUA_VLNGSTR: {
      setivalue(s2v(pIp -> ra), cast_st2S(tsvalue(pIp -> rb)->u.lnglen));
      return;
    }
    default: {  /* try metamethod */
      {const TValue * luaT_gettmbyobj_ret_1;IPCALL(luaT_gettmbyobj,ipluaT_gettmbyobj_0,.ret = luaT_gettmbyobj_ret_1);tm = luaT_gettmbyobj_ret_1;}
      if (l_unlikely(notm(tm)))  /* no metamethod? */
        {IPCALL(luaG_typeerror,ipluaG_typeerror_0);}
      break;
    }
  }
  {lu_byte luaT_callTMres_ret_0;IPCALL(luaT_callTMres,ipluaT_callTMres_0,.ret = &luaT_callTMres_ret_0);}
}