#include "auxsetstr.h"
void auxsetstrFun(void *p) 
{
    auxsetstr *pIp = (auxsetstr*)p;
  int hres;
  TString str;{TString * luaS_new_ret_0; IPCALL(luaS_new,ipluaS_new_0,.ret = luaS_new_ret_0);str = luaS_new_ret_0;}
  {api_checkpop(pIp->L, 1);}
  {luaV_fastset(pIp->t, str, s2v(pIp->L->top.p - 1), hres, luaH_psetstr);}
  if (hres == HOK) {
    {luaV_finishfastset(pIp->L, pIp->t, s2v(pIp->L->top.p - 1));}
    (pIp->L)->top.p--;  /* pop value */
  }
  else {
    {setsvalue2s(pIp->L, pIp->L->top.p, str);}  /* push 'str' (to make it a TValue) */
    {api_incr_top(pIp->L);}
    {luaV_finishset(pIp->L, pIp->t, s2v(pIp->L->top.p - 1), s2v(pIp->L->top.p - 2), hres);}
    (pIp->L)->top.p -= 2;  /* pop value and key */
  }
  {lua_unlock(pIp->L);}  /* lock done by caller */
}