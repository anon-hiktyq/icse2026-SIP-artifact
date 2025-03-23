#include "luaH_psetint.h"
void luaH_psetintFun(void *p) 
{
    luaH_psetint *pIp = (luaH_psetint*)p;
  {lua_assert(!ikeyinarray(pIp->t, pIp->key));}
  const TValue * getintfromhash_ret_0;IPCALL(getintfromhash,ipgetintfromhash_0,.t = pIp->t,.key = pIp->key,.ret = getintfromhash_ret_0);int finishnodeset_ret_0;IPCALL(finishnodeset,ipfinishnodeset_0,.t = pIp->t,.slot = getintfromhash_ret_0,.val = pIp->val,.ret = &finishnodeset_ret_0);*(pIp->ret) =  finishnodeset_ret_0;
}