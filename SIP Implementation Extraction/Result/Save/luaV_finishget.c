#include "luaV_finishget.h"
void luaV_finishgetFun(void *p) 
{
    luaV_finishget *pIp = (luaV_finishget*)p;

  int loop;  /* counter to avoid infinite loops */
  const TValue *tm;  /* metamethod */
  for (loop = 0; loop < MAXTAGLOOP; loop++) {
    if (pIp -> tag == LUA_VNOTABLE) {  /* 'pIp -> t' is not a table? */
      lua_assert(!ttistable(pIp -> t));
      {const TValue * luaT_gettmbyobj_ret_1;IPCALL(luaT_gettmbyobj,ipluaT_gettmbyobj_0,.ret = pIp->luaT_gettmbyobj_ret_1);tm = luaT_gettmbyobj_ret_1;}
      if (l_unlikely(notm(tm)))
        {IPCALL(luaG_typeerror,ipluaG_typeerror_0);}  /* no metamethod */
      /* else will try the metamethod */
    }
    else {  /* 'pIp -> t' is a table */
      tm = fasttm(pIp -> L, hvalue(pIp -> t)->metatable, TM_INDEX);  /* table's metamethod */
      if (tm == NULL) {  /* no metamethod? */
        setnilvalue(s2v(pIp -> val));  /* result is nil */
        *(pIp -> ret) = LUA_VNIL;
      }
      /* else will try the metamethod */
    }
    if (ttisfunction(tm)) {  /* is metamethod a function? */
      {lu_byte luaT_callTMres_ret_0;IPCALL(luaT_callTMres,ipluaT_callTMres_0,.ret = pIp->&luaT_callTMres_ret_0);pIp->tag = luaT_callTMres_ret_0;}  /* call it */
      *(pIp -> ret) = tag; /* return pIp -> tag of the result */
    }
    pIp -> t = tm;  /* else try to access 'tm[pIp -> key]' */
    luaV_fastget(pIp -> t, pIp -> key, s2v(pIp -> val), luaH_get, pIp -> tag);
    if (!tagisempty(pIp -> tag))
      *(pIp -> ret) = tag; /* done */
    /* else repeat (tail call 'luaV_finishget') */
  }
  {IPCALL(luaG_runerror,ipluaG_runerror_0);}
  *(pIp -> ret) = 0; /* to avoid warnings */
}