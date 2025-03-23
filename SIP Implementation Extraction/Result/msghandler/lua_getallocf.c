#include "lua_getallocf.h"
void lua_getallocfFun(void *p) 
{
    lua_getallocf *pIp = (lua_getallocf*)p;
  lua_Alloc f;
  {lua_lock(pIp->L);}
  if ((pIp->ud)) {*pIp->ud = G(pIp->L)->pIp->ud;}
  {f = G(pIp->L)->frealloc;}
  {lua_unlock(pIp->L);}
  *(pIp->ret) =  f;
}