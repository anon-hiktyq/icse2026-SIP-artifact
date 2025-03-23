#include "luaV_equalobj.h"
void luaV_equalobjFun(void *p) 
{
    luaV_equalobj *pIp = (luaV_equalobj*)p;
  const TValue *tm;
  {if (ttypetag(pIp->t1) != ttypetag(pIp->t2)) {  /* not the same variant? */
    {if (ttype(pIp->t1) != ttype(pIp->t2) || ttype(pIp->t1) != LUA_TNUMBER)
      *(pIp->ret) =  0;  /* only numbers can be equal with different variants */
    else {  /* two numbers with different variants */
      /* One of them is an integer. If the other does not have an
         integer value, they cannot be equal; otherwise, compare their
         integer values. */
      lua_Integer i1, i2;
      int luaV_tointegerns_ret_0;IPCALL(luaV_tointegerns,ipluaV_tointegerns_0,.obj = pIp->t2,.p = &i2,.mode = F2Ieq,.ret = &luaV_tointegerns_ret_0);*(pIp->ret) =  (luaV_tointegerns(t1, &i1, F2Ieq) &&
              luaV_tointegerns_ret_0 &&
              i1 == i2);
    }}
  }}
  /* values have same type and same variant */
  {switch (ttypetag(pIp->t1)) {
    case LUA_VNIL: case LUA_VFALSE: case LUA_VTRUE: *(pIp->ret) =  1;
    case LUA_VNUMINT: *(pIp->ret) =  (ivalue(t1) == ivalue(t2));
    case LUA_VNUMFLT: *(pIp->ret) =  luai_numeq(fltvalue(t1), fltvalue(t2));
    case LUA_VLIGHTUSERDATA: *(pIp->ret) =  pvalue(t1) == pvalue(t2);
    case LUA_VLCF: *(pIp->ret) =  fvalue(t1) == fvalue(t2);
    case LUA_VSHRSTR: *(pIp->ret) =  eqshrstr(tsvalue(t1), tsvalue(t2));
    case LUA_VLNGSTR: *(pIp->ret) =  luaS_eqlngstr(tsvalue(t1), tsvalue(t2));
    case LUA_VUSERDATA: {
      {if (uvalue(pIp->t1) == uvalue(pIp->t2)) *(pIp->ret) =  1;
      else if ((pIp->L) == NULL) *(pIp->ret) =  0;}
      {tm = fasttm(pIp->L, uvalue(pIp->t1)->metatable, TM_EQ);}
      if (tm == NULL)
        {tm = fasttm(pIp->L, uvalue(pIp->t2)->metatable, TM_EQ);}
      break;  /* will try TM */
    }
    case LUA_VTABLE: {
      {if (hvalue(pIp->t1) == hvalue(pIp->t2)) *(pIp->ret) =  1;
      else if ((pIp->L) == NULL) *(pIp->ret) =  0;}
      {tm = fasttm(pIp->L, hvalue(pIp->t1)->metatable, TM_EQ);}
      if (tm == NULL)
        {tm = fasttm(pIp->L, hvalue(pIp->t2)->metatable, TM_EQ);}
      break;  /* will try TM */
    }
    default:
      *(pIp->ret) =  gcvalue(t1) == gcvalue(t2);
  }}
  if (tm == NULL)  /* no TM? */
    *(pIp->ret) =  0;  /* objects are different */
  else {
    int tag;{lu_byte luaT_callTMres_ret_0; IPCALL(luaT_callTMres,ipluaT_callTMres_0,.ret = &luaT_callTMres_ret_0);tag = luaT_callTMres_ret_0;}  /* call TM */
    *(pIp->ret) =  !tagisfalse(tag);
  }
}