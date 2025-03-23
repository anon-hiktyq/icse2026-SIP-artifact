#include "LTintfloat.h"
void LTintfloatFun(void *p) 
{
    LTintfloat *pIp = (LTintfloat*)p;
  {if (l_intfitsf(pIp->i))
    *(pIp->ret) =  luai_numlt(cast_num(i), f);  /* compare them as floats */
  else {  /* i < f <=> i < ceil(f) */
    lua_Integer fi;
    {int luaV_flttointeger_ret_0;IPCALL(luaV_flttointeger,ipluaV_flttointeger_0,.n = pIp->f,.p = &fi,.mode = F2Iceil,.ret = &luaV_flttointeger_ret_0);if (luaV_flttointeger_ret_0)  /* fi = ceil(f) */
      *(pIp->ret) =  (pIp->i) < fi;   /* compare them as integers */
    else  /* 'f' is either greater or less than all integers */
      *(pIp->ret) =  (pIp->f) > 0; } /* greater? */
  }}
}