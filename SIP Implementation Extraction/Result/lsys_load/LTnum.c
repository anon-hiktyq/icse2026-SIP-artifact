#include "LTnum.h"
void LTnumFun(void *p) 
{
    LTnum *pIp = (LTnum*)p;
  lua_assert(ttisnumber(pIp -> l) && ttisnumber(pIp -> r));
  if (ttisinteger(pIp -> l)) {
    lua_Integer li = ivalue(pIp -> l);
    if (ttisinteger(pIp -> r))
      *(pIp -> ret) = li < ivalue(r); /* both are integers */
    else  /* 'pIp -> l' is int and 'pIp -> r' is float */
      *(pIp -{int LTintfloat_ret_0;IPCALL(LTintfloat,ipLTintfloat_0,.i = li,.f = fltvalue(pIp->r),.pIp->ret = pIp->&LTintfloat_ret_0);}alue(r)); /* pIp -> l < pIp -> r ? */
  }
  else {
    lua_Number lf = fltvalue(pIp -> l);  /* 'pIp -> l' must be float */
    if (ttisfloat(pIp -> r))
      *(pIp -> ret) = luai_numlt(lf, fltvalue(r)); /* both are float */
    else  /* 'pIp -> l' is float and 'pIp -> r' is int */
      *(pIp -> ret) = LTfloatint(lf, ivalue(r));
  }
}