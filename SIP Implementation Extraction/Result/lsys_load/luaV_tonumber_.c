#include "luaV_tonumber_.h"
void luaV_tonumber_Fun(void *p) 
{
    luaV_tonumber_ *pIp = (luaV_tonumber_*)p;
  TValue v;
  if (ttisinteger(pIp -> obj)) {
    pIp -> *n = cast_num(ivalue(pIp -> obj));
    *(pIp -> ret) = 1;
  }
  else if (l_strton(pIp -> obj, &v)) {  /* string coercible to number? */
    pIp -> *n = nvalue(&v);  /* convert result of 'luaO_str2num' to a float */
    *(pIp -> ret) = 1;
  }
  else
    *(pIp -> ret) = 0; /* conversion failed */
}