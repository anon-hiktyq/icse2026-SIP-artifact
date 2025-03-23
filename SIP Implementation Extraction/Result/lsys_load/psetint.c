#include "psetint.h"
void psetintFun(void *p) 
{
    psetint *pIp = (psetint*)p;
  int hres;
  {luaH_fastseti(pIp->t, pIp->key, pIp->val, hres);}
  *(pIp->ret) =  hres;
}