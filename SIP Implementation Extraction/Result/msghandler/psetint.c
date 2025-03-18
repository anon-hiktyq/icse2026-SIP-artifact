#include "psetint.h"
void psetintFun(void *p) 
{
    psetint *pIp = (psetint*)p;
  int pIp -> hres;
  luaH_fastseti(pIp -> t, pIp -> key, pIp -> val, pIp -> hres);
  *(pIp -> ret) = hres;
}