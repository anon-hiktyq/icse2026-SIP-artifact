#include "luaV_finishset.h"
void luaV_finishsetFun(void *p) 
{
    luaV_finishset *pIp = (luaV_finishset*)p;

  int loop;  /* counter to avoid infinite loops */
  for (loop = 0; loop < MAXTAGLOOP; loop++) {
    const TValue *tm;  /* '__newindex' metamethod */
    if (pIp -> hres != HNOTATABLE) {  /* is 'pIp -> t' a table? */
      Table *h = hvalue(pIp -> t);  /* save 'pIp -> t' table */
      tm = fasttm(pIp -> L, h->metatable, TM_NEWINDEX);  /* get metamethod */
      if (tm == NULL) {  /* no metamethod? */
        {IPCALL(luaH_finishset,ipluaH_finishset_0);}  /* set new value */
        invalidateTMcache(h);
        luaC_barrierback(pIp -> L, obj2gco(h), pIp -> val);
        return;
      }
      /* else will try the metamethod */
    }
    else {  /* not a table; check metamethod */
      tm = luaT_gettmbyobj(pIp -> L, pIp -> t, TM_NEWINDEX);
      if (l_unlikely(notm(tm)))
        luaG_typeerror(pIp -> L, pIp -> t, "index");
    }
    /* try the metamethod */
    if (ttisfunction(tm)) {
      {IPCALL(luaT_callTM,ipluaT_callTM_0);}
      return;
    }
    pIp -> t = tm;  /* else repeat assignment over 'tm' */
    luaV_fastset(pIp -> t, pIp -> key, pIp -> val, pIp -> hres, luaH_pset);
    if (pIp -> hres == HOK)
      return;  /* done */
    /* else 'return luaV_finishset(L, t, key, val, slot)' (loop) */
  }
  {IPCALL(luaG_runerror,ipluaG_runerror_0);}
}