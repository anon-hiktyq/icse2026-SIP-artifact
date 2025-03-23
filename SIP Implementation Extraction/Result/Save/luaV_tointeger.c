#include "luaV_tointeger.h"
void luaV_tointegerFun(void *p) 
{
    luaV_tointeger *pIp = (luaV_tointeger*)p;
  TValue v;
  {int l_strton_ret_0;IPCALL(l_strton,ipl_strton_0,.obj = pIp->obj,.result = &v,.ret = &l_strton_ret_0);if (l_strton_ret_0)  /* does 'obj' point to a numerical string? */
    (pIp->obj) = &v; } /* change it to point to its corresponding number */
  int luaV_tointegerns_ret_0;IPCALL(luaV_tointegerns,ipluaV_tointegerns_0,.obj = pIp->obj,.p = pIp->p,.mode = pIp->mode,.ret = &luaV_tointegerns_ret_0);*(pIp->ret) =  luaV_tointegerns_ret_0;
}