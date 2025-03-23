#include "luaH_newkey.h"
void luaH_newkeyFun(void *p) 
{
    luaH_newkey *pIp = (luaH_newkey*)p;
  {if (!ttisnil(pIp->value)) {  /* do not insert nil values */
    int done;{int insertkey_ret_0; IPCALL(insertkey,ipinsertkey_0,.t = pIp->t,.key = pIp->key,.value = pIp->value,.ret = &insertkey_ret_0);done = insertkey_ret_0;}
    if (!done) {  /* could not find a free place? */
      {IPCALL(rehash,iprehash_0,.L = pIp->L,.t = pIp->t,.ek = pIp->key);}  /* grow table */
      {IPCALL(newcheckedkey,ipnewcheckedkey_0,.t = pIp->t,.key = pIp->key,.value = pIp->value);}  /* insert key in grown table */
    }
    {luaC_barrierback(pIp->L, obj2gco(pIp->t), pIp->key);}
    /* for debugging only: any new key may force an emergency collection */
    {condchangemem(pIp->L, (void)0, (void)0, 1);}
  }}
}