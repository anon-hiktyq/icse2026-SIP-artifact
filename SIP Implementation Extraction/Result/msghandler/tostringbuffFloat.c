#include "tostringbuffFloat.h"
void tostringbuffFloatFun(void *p) 
{
    tostringbuffFloat *pIp = (tostringbuffFloat*)p;
  /* first conversion */
  int len;{len = l_sprintf(pIp->buff, LUA_N2SBUFFSZ, LUA_NUMBER_FMT,
                            (LUAI_UACNUMBER)pIp->n);}
  lua_Number check;{check = lua_str2number(pIp->buff, NULL);}  /* read it back */
  if (check != (pIp->n)) {  /* not enough precision? */
    /* convert again with more precision */
    {len = l_sprintf(pIp->buff, LUA_N2SBUFFSZ, LUA_NUMBER_FMT_N,
                          (LUAI_UACNUMBER)pIp->n);}
  }
  /* looks like an integer? */
  if ((pIp->buff)[strspn((pIp->buff), "-0123456789")] == '\0') {
    {pIp->buff[len++] = lua_getlocaledecpoint();}
    (pIp->buff)[len++] = '0';  /* adds '.0' to result */
  }
  *(pIp->ret) =  len;
}