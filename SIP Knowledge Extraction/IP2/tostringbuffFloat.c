#include "tostringbuffFloat.h"
void tostringbuffFloatFun(void *p) 
{
    tostringbuffFloat *pIp = (tostringbuffFloat*)p;
  /* first conversion */
  int pIp -> len = l_sprintf(pIp -> buff, LUA_N2SBUFFSZ, LUA_NUMBER_FMT,
                            pIp -> (LUAI_UACNUMBER)n);
  lua_Number check = lua_str2number(pIp -> buff, NULL);  /* read it back */
  if (check != pIp -> n) {  /* not enough precision? */
    /* convert again with more precision */
    pIp -> len = l_sprintf(pIp -> buff, LUA_N2SBUFFSZ, LUA_NUMBER_FMT_N,
                          pIp -> (LUAI_UACNUMBER)n);
  }
  /* looks like an integer? */
  if (pIp -> buff[strspn(pIp -> buff, "-0123456789")] == '\0') {
    pIp -> buff[pIp -> len++] = lua_getlocaledecpoint();
    pIp -> buff[pIp -> len++] = '0';  /* adds '.0' to result */
  }
  *(pIp -> ret) = len;
}