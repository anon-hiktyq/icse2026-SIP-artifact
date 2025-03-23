#include "lastlevel.h"
void lastlevelFun(void *p) 
{
    lastlevel *pIp = (lastlevel*)p;
  lua_Debug ar;
  int li = 1, le = 1;
  /* find an upper bound */
  while (lua_getstack((pIp->L), le, &ar)) { li = le; le *= 2; }
  /* do a binary search */
  while (li < le) {
    int m = (li + le)/2;
    {int lua_getstack_ret_1;IPCALL(lua_getstack,iplua_getstack_1,.ret = &lua_getstack_ret_1);if (lua_getstack_ret_1) li = m + 1;
    else le = m;}
  }
  *(pIp->ret) =  le - 1;
}