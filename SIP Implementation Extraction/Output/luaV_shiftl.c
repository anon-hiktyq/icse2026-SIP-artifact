#include "luaV_shiftl.h"
void luaV_shiftlFun(void *p) 
{
    luaV_shiftl *pIp = (luaV_shiftl*)p;
  if (pIp -> y < 0) {  /* shift right? */
    if (pIp -> y <= -NBITS) return 0;
    else return intop(>>, pIp -> x, -pIp -> y);
  }
  else {  /* shift left */
    if (pIp -> y >= NBITS) return 0;
    else return intop(<<, pIp -> x, pIp -> y);
  }
}