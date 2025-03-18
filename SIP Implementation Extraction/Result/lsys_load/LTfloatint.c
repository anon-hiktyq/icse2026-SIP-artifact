#include "LTfloatint.h"
void LTfloatintFun(void *p) 
{
    LTfloatint *pIp = (LTfloatint*)p;
  if (l_intfitsf(pIp -> i))
    *(pIp -> ret) = luai_numlt(f, cast_num(i)); /* compare them as floats */
  else {  /* pIp -> f < pIp -> i <=> floor(pIp -> f) < pIp -> i */
    lua_Integer fi;
    {int luaV_flttointeger_ret_0;IPCALL(luaV_flttointeger,ipluaV_flttointeger_0,.n = f,.p = &fi,.mode = F2Ifloor,.ret = pIp->&luaV_flttointeger_ret_0);pIp->if ((luaV_flttointeger_ret_0)  /* fi = floor(pIp -> f) */
      *(pIp -> ret) = fi < i;  /* compare them as integers */
    else  /* 'pIp -> f' is either greater or less than all integers */
      *(pIp -> ret} = f < 0; /* less? */
  }
}