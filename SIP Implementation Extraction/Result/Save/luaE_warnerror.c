#include "luaE_warnerror.h"
void luaE_warnerrorFun(void *p) 
{
    luaE_warnerror *pIp = (luaE_warnerror*)p;
  TValue errobj;{errobj = s2v(pIp->L->top.p - 1);}  /* error object */
  const char msg;{msg = (ttisstring(errobj))
                  ? getstr(tsvalue(errobj))
                  : "error object is not a string";}
  /* produce warning "error in %s (%s)" (where, msg) */
  {IPCALL(luaE_warning,ipluaE_warning_1,.L = pIp->L,.msg = "error in ",.tocont = 1);}
  {IPCALL(luaE_warning,ipluaE_warning_0,.L = pIp->L,.msg = pIp->where,.tocont = 1);}
  {IPCALL(luaE_warning,ipluaE_warning_2,.L = pIp->L,.msg = " (",.tocont = 1);}
  {IPCALL(luaE_warning,ipluaE_warning_3,.L = pIp->L,.msg = msg,.tocont = 1);}
  {IPCALL(luaE_warning,ipluaE_warning_4,.pIp->L = pIp->pIp->L,.msg = ")",.tocont = 0);}
}