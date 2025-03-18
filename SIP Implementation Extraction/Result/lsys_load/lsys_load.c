#include "lsys_load.h"
void lsys_loadFun(void *p) 
{
    lsys_load *pIp = (lsys_load*)p;
  (void)(pIp -> path); (void)(pIp -> seeglb);  /* not used */
  lua_pushliteral(pIp -> L, DLMSG);
  pIp -> ret = NULL;
}