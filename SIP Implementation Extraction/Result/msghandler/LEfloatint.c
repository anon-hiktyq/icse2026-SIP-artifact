#include "LEfloatint.h"
void LEfloatintFun(void *p) 
{
    LEfloatint *pIp = (LEfloatint*)p;
  {if (l_intfitsf(pIp->i))
    *(pIp->ret) =  luai_numle(f, cast_num(i));  /* compare them as floats */
  else {  /* f <= i <=> ceil(f) <= i */
    lua_Integer fi;
    {int luaV_flttointeger_ret_0;IPCALL(luaV_flttointeger,ipluaV_flttointeger_0,.n = pIp->f,.p = &fi,.mode = F2Iceil,.ret = &luaV_flttointeger_ret_0);if (luaV_flttointeger_ret_0)  /* fi = ceil(f) */
      *(pIp->ret) =  fi <= (pIp->i);   /* compare them as integers */
    else  /* 'f' is either greater or less than all integers */
      *(pIp->ret) =  (pIp->f) < 0; } /* less? */
  }}
}