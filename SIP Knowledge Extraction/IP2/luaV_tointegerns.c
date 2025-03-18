#include "luaV_tointegerns.h"
void luaV_tointegernsFun(void *p) 
{
    luaV_tointegerns *pIp = (luaV_tointegerns*)p;
  if (ttisfloat(pIp -> obj))
    *(pIp -> ret) = luaV_flttointeger(fltvalue(obj), p, mode);
  else if (ttisinteger(pIp -> obj)) {
    pIp -> *p = ivalue(pIp -> obj);
    *(pIp -> ret) = 1;
  }
  else
    *(pIp -> ret) = 0;
}