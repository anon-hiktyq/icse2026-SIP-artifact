#include "luaS_hash.h"
void luaS_hashFun(void *p) 
{
    luaS_hash *pIp = (luaS_hash*)p;
  unsigned int pIp -> h = pIp -> seed ^ cast_uint(pIp -> l);
  for (; pIp -> l > 0; pIp -> l--)
    pIp -> h ^= ((pIp -> h<<5) + (pIp -> h>>2) + cast_byte(pIp -> str[pIp -> l - 1]));
  *(pIp -> ret) = h;
}