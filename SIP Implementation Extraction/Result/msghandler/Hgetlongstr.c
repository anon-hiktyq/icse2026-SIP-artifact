#include "Hgetlongstr.h"
void HgetlongstrFun(void *p) 
{
    Hgetlongstr *pIp = (Hgetlongstr*)p;
  TValue ko;
  lua_assert(!strisshr(pIp -> key));
  setsvalue(cast(lua_State *, NULL), &ko, pIp -> key);
  pIp -> ret = getgeneric(t, &ko, 0); /* for long strings, use generic case */
}