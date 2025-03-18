#include "lua_createtable.h"
void lua_createtableFun(void *p) 
{
    lua_createtable *pIp = (lua_createtable*)p;
  Table *t;
  lua_lock(pIp -> L);
  {Table * luaH_new_ret_0;IPCALL(luaH_new,ipluaH_new_0,.ret = luaH_new_ret_0);t = luaH_new_ret_0;}
  sethvalue2s(pIp -> L, pIp -> L->top.p, t);
  api_incr_top(pIp -> L);
  if (pIp -> narray > 0 || pIp -> nrec > 0)
    {IPCALL(luaH_resize,ipluaH_resize_0);}
  luaC_checkGC(pIp -> L);
  lua_unlock(pIp -> L);
}