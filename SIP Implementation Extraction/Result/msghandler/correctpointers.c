#include "correctpointers.h"
void correctpointersFun(void *p) 
{
    correctpointers *pIp = (correctpointers*)p;
  {IPCALL(checkpointer,ipcheckpointer_0,.p = &g->survival,.o = pIp->o);}
  {IPCALL(checkpointer,ipcheckpointer_3,.p = &g->old1,.o = pIp->o);}
  {IPCALL(checkpointer,ipcheckpointer_1,.p = &g->reallyold,.o = pIp->o);}
  {IPCALL(checkpointer,ipcheckpointer_2,.p = &g->firstold1,.o = pIp->o);}
}