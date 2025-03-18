#include "iscleared.h"
void isclearedFun(void *p) 
{
    iscleared *pIp = (iscleared*)p;
  if (pIp -> o == NULL) return 0;  /* non-collectable value */
  else if (novariant(pIp -> o->tt) == LUA_TSTRING) {
    markobject(pIp -> g, pIp -> o);  /* strings are 'values', so are never weak */
    *(pIp -> ret) = 0;
  }
  else return iswhite(pIp -> o);
}