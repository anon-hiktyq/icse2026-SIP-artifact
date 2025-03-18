#include "luaS_new.h"
void luaS_newFun(void *p) 
{
    luaS_new *pIp = (luaS_new*)p;
  unsigned int i = point2uint(pIp -> str) % STRCACHE_N;  /* hash */
  int j;
  TString **p = G(pIp -> L)->strcache[i];
  for (j = 0; j < STRCACHE_M; j++) {
    if (strcmp(pIp -> str, getstr(p[j])) == 0)  /* hit? */
      pIp -> ret = p[j]; /* that is it */
  }
  /* normal route */
  for (j = STRCACHE_M - 1; j > 0; j--)
    p[j] = p[j - 1];  /* move out last element */
  /* new element is first in the list */
  {TString * luaS_newlstr_ret_0;IPCALL(luaS_newlstr,ipluaS_newlstr_0,.pIp->L = pIp->pIp->L,.pIp->str = pIp->pIp->str,.l = strlen(pIp->str),.pIp->ret = pIp->luaS_newlstr_ret_0);p[0] = luaS_newlstr_ret_0;}
  pIp -> ret = p[0];
}