#include "luaS_clearcache.h"
void luaS_clearcacheFun(void *p) 
{
    luaS_clearcache *pIp = (luaS_clearcache*)p;
  int i, j;
  for (i = 0; i < STRCACHE_N; i++)
    for (j = 0; j < STRCACHE_M; j++) {
      if (iswhite(pIp -> g->strcache[i][j]))  /* will entry be collected? */
        pIp -> g->strcache[i][j] = pIp -> g->memerrmsg;  /* replace it with something fixed */
    }
}