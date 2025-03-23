#include "luaL_buffinit.h"
void luaL_buffinitFun(void *p) 
{
    luaL_buffinit *pIp = (luaL_buffinit*)p;
  (pIp->B)->L = (pIp->L);
  (pIp->B)->b = (pIp->B)->init.b;
  (pIp->B)->n = 0;
  (pIp->B)->size = LUAL_BUFFERSIZE;
  {IPCALL(lua_pushlightuserdata,iplua_pushlightuserdata_0);}  /* push placeholder */
}