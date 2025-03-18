#include "luaH_setint.h"
void luaH_setintFun(void *p) 
{
    luaH_setint *pIp = (luaH_setint*)p;
  unsigned ik = ikeyinarray(pIp -> t, pIp -> key);
  if (ik > 0)
    obj2arr(pIp -> t, ik - 1, pIp -> value);
  else {
    int ok;{const TValue * getintfromhash_ret_0;IPCALL(getintfromhash,ipgetintfromhash_0,.t = pIp->t,.key = pIp->key,.ret = getintfromhash_ret_0);int rawfinishnodeset_ret_0;IPCALL(rawfinishnodeset,iprawfinishnodeset_0,.slot = getintfromhash_ret_0,.val = value,.ret = &rawfinishnodeset_ret_0);ok = rawfinishnodeset_ret_0}
    if (!ok) {
      TValue k;
      setivalue(&k, pIp -> key);
      {IPCALL(luaH_newkey,ipluaH_newkey_0,.L = pIp->L,.t = pIp->t,.key = pIp->&k,.value = pIp->value);}
    }
  }
}