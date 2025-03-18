#include "LEfloatint.h"
void LEfloatintFun(void *p) 
{
    LEfloatint *pIp = (LEfloatint*)p;
  if (l_intfitsf(pIp -> i))
    *(pIp -> ret) = luai_numle(f, cast_num(i)); /* compare them as floats */
  else {  /* pIp -> f <= pIp -> i <=> ceil(pIp -> f) <= pIp -> i */
    lua_Integer fi;
    {int luaV_flttointeger_ret_0;IPCALL(luaV_flttointeger,ipluaV_flttointeger_0,.n = f,.p = &fi,.mode = F2Iceil,.ret = pIp->&luaV_flttointeger_ret_0);pIp->if ((luaV_flttointeger_ret_0)  /* fi = ceil(pIp -> f) */
      *(pIp -> ret) = fi <= i;  /* compare them as integers */
    else  /* 'pIp -> f' is either greater or less than all integers */
      *(pIp -> ret} = f < 0; /* less? */
  }
}