#include "checkclosemth.h"
void checkclosemthFun(void *p) 
{
    checkclosemth *pIp = (checkclosemth*)p;
  const TValue tm;{tm = luaT_gettmbyobj(pIp->L, s2v(pIp->level), TM_CLOSE);}
  {if (ttisnil(tm)) {  /* no metamethod? */
    int idx;{idx = cast_int(pIp->level - pIp->L->ci->func.p);}  /* variable index */
    const char vname;{const char * luaG_findlocal_ret_0; IPCALL(luaG_findlocal,ipluaG_findlocal_0,.ret = luaG_findlocal_ret_0);vname = luaG_findlocal_ret_0;}
    if (vname == NULL) vname = "?";
    {IPCALL(luaG_runerror,ipluaG_runerror_0);}
  }}
}