#include "touserdata.h"
void touserdataFun(void *p) 
{
    touserdata *pIp = (touserdata*)p;
  switch (ttype(pIp -> o)) {
    case LUA_TUSERDATA: return getudatamem(uvalue(pIp -> o));
    case LUA_TLIGHTUSERDATA: return pvalue(pIp -> o);
    default: return NULL;
  }
}