#include "LTfloatint.h"
void LTfloatintFun(void *p) 
{
    LTfloatint *pIp = (LTfloatint*)p;
  {if (l_intfitsf(pIp->i))
    *(pIp->ret) =  luai_numlt(f, cast_num(i));  /* compare them as floats */
  else {  /* f < i <=> floor(f) < i */
    lua_Integer fi;
    {int luaV_flttointeger_ret_0;IPCALL(luaV_flttointeger,ipluaV_flttointeger_0,.n = pIp->f,.p = &fi,.mode = F2Ifloor,.ret = &luaV_flttointeger_ret_0);if (luaV_flttointeger_ret_0)  /* fi = floor(f) */
      *(pIp->ret) =  fi < (pIp->i);   /* compare them as integers */
    else  /* 'f' is either greater or less than all integers */
      *(pIp->ret) =  (pIp->f) < 0; } /* less? */
  }}
}