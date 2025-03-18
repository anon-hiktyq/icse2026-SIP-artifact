#include "luaL_prepbuffsize.h"
void luaL_prepbuffsizeFun(void *p) 
{
    luaL_prepbuffsize *pIp = (luaL_prepbuffsize*)p;
  pIp -> ret = prepbuffsize(B, sz, -1);
}