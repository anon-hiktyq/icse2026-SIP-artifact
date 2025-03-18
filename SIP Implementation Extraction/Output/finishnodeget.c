#include "finishnodeget.h"
void finishnodegetFun(void *p) 
{
    finishnodeget *pIp = (finishnodeget*)p;
  if (!ttisnil(pIp -> val)) {
    setobj(((lua_State*)NULL), pIp -> res, pIp -> val);
  }
  *(pIp -> ret) = ttypetag(val);
}