#include "luaH_getstr.h"
void luaH_getstrFun(void *p) 
{
    luaH_getstr *pIp = (luaH_getstr*)p;
  *(pIp -> ret) = finishnodeget(Hgetstr(t, key), res);
}