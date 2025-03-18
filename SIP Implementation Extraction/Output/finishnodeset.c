#include "finishnodeset.h"
void finishnodesetFun(void *p) 
{
    finishnodeset *pIp = (finishnodeset*)p;
  if (!ttisnil(pIp -> slot)) {
    setobj(((lua_State*)NULL), cast(TValue*, pIp -> slot), pIp -> val);
    *(pIp -> ret) = HOK; /* success */
  }
  else
    *(pIp -> ret) = retpsetcode(t, slot);
}