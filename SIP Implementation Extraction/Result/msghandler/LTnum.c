#include "LTnum.h"
void LTnumFun(void *p) 
{
    LTnum *pIp = (LTnum*)p;
  {lua_assert(ttisnumber(pIp->l) && ttisnumber(pIp->r));}
  {if (ttisinteger(pIp->l)) {
    lua_Integer li;{li = ivalue(pIp->l);}
    {if (ttisinteger(pIp->r))
      *(pIp->ret) =  li < ivalue(r);  /* both are integers */
    else  /* 'l' is int and 'r' is float */
      *(pIp->ret) =  LTintfloat(li, fltvalue(r)); } /* l < r ? */
  }
  else {
    lua_Number lf;{lf = fltvalue(pIp->l);}  /* 'l' must be float */
    {if (ttisfloat(pIp->r))
      *(pIp->ret) =  luai_numlt(lf, fltvalue(r));  /* both are float */
    else  /* 'l' is float and 'r' is int */
      *(pIp->ret) =  LTfloatint(lf, ivalue(r));}
  }}
}