#include "luaH_psetshortstr.h"
void luaH_psetshortstrFun(void *p) 
{
    luaH_psetshortstr *pIp = (luaH_psetshortstr*)p;
  const TValue slot;{const TValue * luaH_Hgetshortstr_ret_0; IPCALL(luaH_Hgetshortstr,ipluaH_Hgetshortstr_0,.t = pIp->t,.key = pIp->key,.ret = luaH_Hgetshortstr_ret_0);slot = luaH_Hgetshortstr_ret_0;}
  {if (!ttisnil(slot)) {  /* key already has a value? (all too common) */
    {setobj(((lua_State*)NULL), cast(TValue*, slot), pIp->val);}  /* update it */
    *(pIp->ret) =  HOK;  /* done */
  }
  else {if (checknoTM(pIp->t->metatable, TM_NEWINDEX)) {  /* no metamethod? */
    {if (ttisnil(pIp->val))  /* new value is nil? */
      *(pIp->ret) =  HOK; } /* done (value is already nil/absent) */
    {if (isabstkey(slot) &&  /* pIp->key is absent? */
       !(isblack(pIp->t) && iswhite(pIp->key))) {  /* and don't need barrier? */
      TValue tk;  /* key as a TValue */
      setsvalue(cast(lua_State *, NULL), &tk, (pIp->key));
      {int insertkey_ret_0;IPCALL(insertkey,ipinsertkey_0,.t = pIp->t,.key = &tk,.value = pIp->val,.ret = &insertkey_ret_0);if (insertkey_ret_0) {  /* insert key, if there is space */
        {invalidateTMcache(pIp->t);}
        *(pIp->ret) =  HOK;
      }}
    }}
  }}}
  /* Else, either table has new-index metamethod, or it needs barrier,
     or it needs to rehash for the new key. In any of these cases, the
     operation cannot be completed here. Return a code for the caller. */
  int retpsetcode_ret_0;IPCALL(retpsetcode,ipretpsetcode_0,.t = pIp->t,.slot = slot,.ret = &retpsetcode_ret_0);*(pIp->ret) =  retpsetcode_ret_0;
}