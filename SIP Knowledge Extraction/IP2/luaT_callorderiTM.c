#include "luaT_callorderiTM.h"
void luaT_callorderiTMFun(void *p) 
{
    luaT_callorderiTM *pIp = (luaT_callorderiTM*)p;

  TValue aux; const TValue *p2;
  if (pIp -> isfloat) {
    setfltvalue(&aux, cast_num(pIp -> v2));
  }
  else
    setivalue(&aux, pIp -> v2);
  if (pIp -> flip) {  /* arguments were exchanged? */
    p2 = pIp -> p1; pIp -> p1 = &aux;  /* correct them */
  }
  else
    p2 = &aux;
  *(pIp -> ret) = luaT_callorderTM(L, p1, p2, event);
}