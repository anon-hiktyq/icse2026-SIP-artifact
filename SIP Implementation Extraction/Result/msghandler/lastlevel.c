#include "lastlevel.h"
void lastlevelFun(void *p) 
{
    lastlevel *pIp = (lastlevel*)p;
  lua_Debug ar;
  int li = 1, le = 1;
  /* find an upper bound */
  while (lua_getstack(pIp -> L, le, &ar)) { li = le; le *= 2; }
  /* do a binary search */
  while (li < le) {
    int m = (li + le)/2;
    {int lua_getstack_ret_0;IPCALL(lua_getstack,iplua_getstack_0,.ret = pIp->&lua_getstack_ret_0);if ((lua_getstack_ret_0) li = m + 1;
    else le = m}
  }
  *(pIp -> ret) = le - 1;
}