#include "fullgen.h"
void fullgenFun(void *p) 
{
    fullgen *pIp = (fullgen*)p;
  {IPCALL(minor2inc,ipminor2inc_0,.L = pIp->L,.g = pIp->g,.kind = KGC_INC);}
  {IPCALL(entergen,ipentergen_0,.L = pIp->L,.g = pIp->g);}
}