#include "touserdata.h"
void touserdataFun(void *p) 
{
    touserdata *pIp = (touserdata*)p;
  {switch (ttype(pIp->o)) {
    case LUA_TUSERDATA: pIp->ret =  getudatamem(uvalue(o));
    case LUA_TLIGHTUSERDATA: pIp->ret =  pvalue(o);
    default: pIp->ret =  NULL;
  }}
}