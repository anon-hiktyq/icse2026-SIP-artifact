#include "l_strton.h"
void l_strtonFun(void *p) 
{
    l_strton *pIp = (l_strton*)p;
  lua_assert(pIp -> obj != pIp -> result);
  if (!cvt2num(pIp -> obj))  /* is object not a string? */
    *(pIp -> ret) = 0;
  else {
    TString *st = tsvalue(pIp -> obj);
    size_t stlen;
    const char *s = getlstr(st, stlen);
    *(pIp -> ret) = (luaO_str2num(s, result) == stlen + 1);
  }
}