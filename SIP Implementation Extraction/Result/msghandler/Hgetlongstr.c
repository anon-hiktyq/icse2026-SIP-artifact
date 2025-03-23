#include "Hgetlongstr.h"
void HgetlongstrFun(void *p) 
{
    Hgetlongstr *pIp = (Hgetlongstr*)p;
  TValue ko;
  {lua_assert(!strisshr(pIp->key));}
  setsvalue(cast(lua_State *, NULL), &ko, (pIp->key));
  const TValue * getgeneric_ret_0;IPCALL(getgeneric,ipgetgeneric_0,.t = pIp->t,.key = &ko,.deadok = 0,.ret = getgeneric_ret_0);pIp->ret =  getgeneric_ret_0;  /* for long strings, use generic case */
}