#include "luaV_equalobj.h"
void luaV_equalobjFun(void *p) 
{
    luaV_equalobj *pIp = (luaV_equalobj*)p;
  const TValue *tm;
  if (ttypetag(pIp -> t1) != ttypetag(pIp -> t2)) {  /* not the same variant? */
    if (ttype(pIp -> t1) != ttype(pIp -> t2) || ttype(pIp -> t1) != LUA_TNUMBER)
      *(pIp -> ret) = 0; /* only numbers can be equal with different variants */
    else {  /* two numbers with different variants */
      /* One of them is an integer. If the other does not have an
         integer value, they cannot be equal; otherwise, compare their
         integer values. */
      lua_Integer i1, i2;
      return (luaV_tointegerns(pIp -> t1, &i1, F2Ieq) &&
              luaV_tointegerns(pIp -> t2, &i2, F2Ieq) &&
              i1 == i2);
    }
  }
  /* values have same type and same variant */
  switch (ttypetag(pIp -> t1)) {
    case LUA_VNIL: case LUA_VFALSE: case LUA_VTRUE: return 1;
    case LUA_VNUMINT: return (ivalue(pIp -> t1) == ivalue(pIp -> t2));
    case LUA_VNUMFLT: return luai_numeq(fltvalue(pIp -> t1), fltvalue(pIp -> t2));
    case LUA_VLIGHTUSERDATA: return pvalue(pIp -> t1) == pvalue(pIp -> t2);
    case LUA_VLCF: return fvalue(pIp -> t1) == fvalue(pIp -> t2);
    case LUA_VSHRSTR: return eqshrstr(tsvalue(pIp -> t1), tsvalue(pIp -> t2));
    case LUA_VLNGSTR: return {int luaS_eqlngstr_ret_3;IPCALL(luaS_eqlngstr,ipluaS_eqlngstr_0,.ret = pIp->&luaS_eqlngstr_ret_3);}
    case LUA_VUSERDATA: {
      if (uvalue(pIp -> t1) == uvalue(pIp -> t2)) return 1;
      else if (pIp -> L == NULL) return 0;
      tm = fasttm(pIp -> L, uvalue(pIp -> t1)->metatable, TM_EQ);
      if (tm == NULL)
        tm = {const TValue * luaT_gettm_ret_2;IPCALL(luaT_gettm,ipluaT_gettm_1,.ret = pIp->luaT_gettm_ret_2);}
      break;  /* will try TM */
    }
    case LUA_VTABLE: {
      if (hvalue(pIp -> t1) == hvalue(pIp -> t2)) return 1;
      else if (pIp -> L == NULL) return 0;
      tm = fasttm(pIp -> L, hvalue(pIp -> t1)->metatable, TM_EQ);
      if (tm == NULL)
        tm = {const TValue * luaT_gettm_ret_1;IPCALL(luaT_gettm,ipluaT_gettm_0,.ret = pIp->luaT_gettm_ret_1);}
      break;  /* will try TM */
    }
    default:
      *(pIp -> ret) = gcvalue(t1) == gcvalue(t2);
  }
  if (tm == NULL)  /* no TM? */
    *(pIp -> ret) = 0; /* objects are different */
  else {
    int tag;{lu_byte luaT_callTMres_ret_0;IPCALL(luaT_callTMres,ipluaT_callTMres_0,.ret = pIp->&luaT_callTMres_ret_0);tag = luaT_callTMres_ret_0}  /* call TM */
    *(pIp -> ret) = !tagisfalse(tag);
  }
}