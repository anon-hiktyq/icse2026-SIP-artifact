#include "lua_getstack.h"
void lua_getstackFun(void *p) 
{
    lua_getstack *pIp = (lua_getstack*)p;
  int status;
  CallInfo *ci;
  if ((pIp->level) < 0) *(pIp->ret) =  0;  /* invalid (negative) level */
  {lua_lock(pIp->L);}
  for (ci = (pIp->L)->ci; (pIp->level) > 0 && ci != &(pIp->L)->base_ci; ci = ci->previous)
    (pIp->level)--;
  if ((pIp->level) == 0 && ci != &(pIp->L)->base_ci) {  /* level found? */
    status = 1;
    (pIp->ar)->i_ci = ci;
  }
  else status = 0;  /* no such level */
  {lua_unlock(pIp->L);}
  *(pIp->ret) =  status;
}