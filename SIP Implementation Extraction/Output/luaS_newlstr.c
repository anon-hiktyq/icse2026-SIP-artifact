#include "luaS_newlstr.h"
void luaS_newlstrFun(void *p) 
{
    luaS_newlstr *pIp = (luaS_newlstr*)p;
  if (pIp -> l <= LUAI_MAXSHORTLEN)  /* short string? */
    pIp -> ret = internshrstr(L, str, l);
  else {
    TString *ts;
    if (l_unlikely(pIp -> l * sizeof(char) >= (MAX_SIZE - sizeof(TString))))
      {IPCALL(luaM_toobig,ipluaM_toobig_0);}
    {TString * luaS_createlngstrobj_ret_0;IPCALL(luaS_createlngstrobj,ipluaS_createlngstrobj_0,.L = pIp->L,.l = pIp->l,.ret = pIp->luaS_createlngstrobj_ret_0);ts = luaS_createlngstrobj_ret_0;}
    memcpy(getlngstr(ts), pIp -> str, pIp -> l * sizeof(char));
    pIp -> ret = ts;
  }
}