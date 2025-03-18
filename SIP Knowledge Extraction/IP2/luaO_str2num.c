#include "luaO_str2num.h"
void luaO_str2numFun(void *p) 
{
    luaO_str2num *pIp = (luaO_str2num*)p;
  lua_Integer i; lua_Number n;
  const char *e;
  {const char * l_str2int_ret_0;IPCALL(l_str2int,ipl_str2int_0,.s = pIp->s,.result = &i,.ret = pIp->l_str2int_ret_0);if ((e = (l_str2int_ret_0) != NULL) {  /* try as an integer */
    setivalue(pIp -> o, i);
  }
  else if ((e = l_str2d(pIp -> s, &n)) != NULL) {  /* else try as a float */
    setfltvalue(pIp -> o, n);
  }
  else
    *(pIp ->}ret) = 0; /* conversion failed */
  *(pIp -> ret) = ct_diff2sz(e - s) + 1; /* success; return string size */
}