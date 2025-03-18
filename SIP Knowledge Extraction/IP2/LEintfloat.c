#include "LEintfloat.h"
void LEintfloatFun(void *p) 
{
    LEintfloat *pIp = (LEintfloat*)p;
  if (l_intfitsf(pIp -> i))
    *(pIp -> ret) = luai_numle(cast_num(i), f); /* compare them as floats */
  else {  /* pIp -> i <= pIp -> f <=> pIp -> i <= floor(pIp -> f) */
    lua_Integer fi;
    {int luaV_flttointeger_ret_0;IPCALL(luaV_flttointeger,ipluaV_flttointeger_0,.n = f,.p = &fi,.mode = F2Ifloor,.ret = pIp->&luaV_flttointeger_ret_0);pIp->if ((luaV_flttointeger_ret_0)  /* fi = floor(pIp -> f) */
      *(pIp -> ret) = i <= fi;  /* compare them as integers */
    else  /* 'pIp -> f' is either greater or less than all integers */
      *(pIp -> ret} = f > 0; /* greater? */
  }
}