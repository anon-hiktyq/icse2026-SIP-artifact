#include "l_strton.h"
void l_strtonFun(void *p) 
{
    l_strton *pIp = (l_strton*)p;
  {lua_assert(pIp->obj != pIp->result);}
  {if (!cvt2num(pIp->obj))  /* is object not a string? */
    *(pIp->ret) =  0;
  else {
    TString st;{st = tsvalue(pIp->obj);}
    size_t stlen;
    const char s;{s = getlstr(st, stlen);}
    size_t luaO_str2num_ret_0;IPCALL(luaO_str2num,ipluaO_str2num_0,.ret = &luaO_str2num_ret_0);*(pIp->ret) =  (luaO_str2num_ret_0 == stlen + 1);
  }}
}