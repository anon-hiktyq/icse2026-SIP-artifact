#include "LTintfloat.h"
void LTintfloatFun(void *p) 
{
    LTintfloat *pIp = (LTintfloat*)p;
  if (l_intfitsf(pIp -> i))
    *(pIp -> ret) = luai_numlt(cast_num(i), f); /* compare them as floats */
  else {  /* pIp -> i < pIp -> f <=> pIp -> i < ceil(pIp -> f) */
    lua_Integer fi;
    {int luaV_flttointeger_ret_0;IPCALL(luaV_flttointeger,ipluaV_flttointeger_0,.n = f,.p = &fi,.mode = F2Iceil,.ret = pIp->&luaV_flttointeger_ret_0);pIp->if ((luaV_flttointeger_ret_0)  /* fi = ceil(pIp -> f) */
      *(pIp -> ret) = i < fi;  /* compare them as integers */
    else  /* 'pIp -> f' is either greater or less than all integers */
      *(pIp -> ret} = f > 0; /* greater? */
  }
}