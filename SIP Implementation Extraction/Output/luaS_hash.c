#include "luaS_hash.h"
void luaS_hashFun(void *p) 
{
    luaS_hash *pIp = (luaS_hash*)p;
  unsigned int h = pIp -> seed ^ cast_uint(pIp -> l);
  for (; pIp -> l > 0; pIp -> l--)
    h ^= ((h<<5) + (h>>2) + cast_byte(pIp -> str[pIp -> l - 1]));
  *(pIp -> ret) = h;
}