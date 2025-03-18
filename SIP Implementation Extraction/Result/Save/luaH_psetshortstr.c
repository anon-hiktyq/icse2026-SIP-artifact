#include "luaH_psetshortstr.h"
void luaH_psetshortstrFun(void *p) 
{
    luaH_psetshortstr *pIp = (luaH_psetshortstr*)p;
  const TValue *slot;{const TValue * luaH_Hgetshortstr_ret_0;IPCALL(luaH_Hgetshortstr,ipluaH_Hgetshortstr_0,.t = pIp->t,.key = pIp->key,.ret = pIp->luaH_Hgetshortstr_ret_0);*slot = luaH_Hgetshortstr_ret_0}
  if (!ttisnil(slot)) {  /* pIp -> key already has a value? (all too common) */
    setobj(((lua_State*)NULL), cast(TValue*, slot), pIp -> val);  /* update it */
    *(pIp -> ret) = HOK; /* done */
  }
  else if (checknoTM(pIp -> t->metatable, TM_NEWINDEX)) {  /* no metamethod? */
    if (ttisnil(pIp -> val))  /* new value is nil? */
      *(pIp -> ret) = HOK; /* done (value is already nil/absent) */
    if (isabstkey(slot) &&  /* pIp -> key is absent? */
       !(isblack(pIp -> t) && iswhite(pIp -> key))) {  /* and don'pIp -> t need barrier? */
      TValue tk;  /* pIp -> key as a TValue */
      setsvalue(cast(lua_State *, NULL), &tk, pIp -> key);
      if (insertkey(pIp -> t, &tk, pIp -> val)) {  /* insert pIp -> key, if there is space */
        invalidateTMcache(pIp -> t);
        *(pIp -> ret) = HOK;
      }
    }
  }
  /* Else, either table has new-index metamethod, or it needs barrier,
     or it needs to rehash for the new pIp -> key. In any of these cases, the
     operation cannot be completed here. Return a code for the caller. */
  *(pIp -> ret) = retpsetcode(t, slot);
}