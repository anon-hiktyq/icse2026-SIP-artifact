#include "luaH_getshortstr.h"
void luaH_getshortstrFun(void *p) 
{
    luaH_getshortstr *pIp = (luaH_getshortstr*)p;
  *(pIp -> ret) = finishnodeget(luaH_Hgetshortstr(t, key), res);
}