#include "checkSizes.h"
void checkSizesFun(void *p) 
{
    checkSizes *pIp = (checkSizes*)p;
  if (!pIp -> g->gcemergency) {
    if (pIp -> g->strt.nuse < pIp -> g->strt.size / 4)  /* string table too big? */
      {IPCALL(luaS_resize,ipluaS_resize_0);}
  }
}