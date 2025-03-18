#include "rawfinishnodeset.h"
void rawfinishnodesetFun(void *p) 
{
    rawfinishnodeset *pIp = (rawfinishnodeset*)p;
  if (isabstkey(pIp -> slot))
    *(pIp -> ret) = 0; /* no pIp -> slot with that key */
  else {
    setobj(((lua_State*)NULL), cast(TValue*, pIp -> slot), pIp -> val);
    *(pIp -> ret) = 1; /* success */
  }
}