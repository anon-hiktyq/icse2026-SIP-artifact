#include "luaF_getlocalname.h"
void luaF_getlocalnameFun(void *p) 
{
    luaF_getlocalname *pIp = (luaF_getlocalname*)p;
  int i;
  for (i = 0; i<(pIp->f)->sizelocvars && (pIp->f)->locvars[i].startpc <= (pIp->pc); i++) {
    if ((pIp->pc) < (pIp->f)->locvars[i].endpc) {  /* is variable active? */
      (pIp->local_number)--;
      if ((pIp->local_number) == 0)
        pIp->ret =  getstr(f->locvars[i].varname);
    }
  }
  pIp->ret =  NULL;  /* not found */
}