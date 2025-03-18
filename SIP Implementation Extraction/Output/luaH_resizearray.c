#include "luaH_resizearray.h"
void luaH_resizearrayFun(void *p) 
{
    luaH_resizearray *pIp = (luaH_resizearray*)p;
  unsigned nsize = allocsizenode(pIp -> t);
  {IPCALL(luaH_resize,ipluaH_resize_0,.L = pIp->L,.t = pIp->t,.newasize = nasize,.nhsize = nsize);}
}