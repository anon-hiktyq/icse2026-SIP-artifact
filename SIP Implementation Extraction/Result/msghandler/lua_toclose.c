#include "lua_toclose.h"
void lua_tocloseFun(void *p) 
{
    lua_toclose *pIp = (lua_toclose*)p;
  StkId o;
  lua_lock(pIp -> L);
  {StkId index2stack_ret_0;IPCALL(index2stack,ipindex2stack_0,.L = pIp->L,.idx = pIp->idx,.ret = &index2stack_ret_0);o = index2stack_ret_0;}
  api_check(pIp -> L, pIp -> L->tbclist.p < o, "given index below or equal a marked one");
  {IPCALL(luaF_newtbcupval,ipluaF_newtbcupval_0);}  /* create new to-be-closed upvalue */
  pIp -> L->ci->callstatus |= CIST_TBC;  /* mark that function has TBC slots */
  lua_unlock(pIp -> L);
}