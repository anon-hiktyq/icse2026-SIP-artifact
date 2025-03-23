#include "restartcollection.h"
void restartcollectionFun(void *p) 
{
    restartcollection *pIp = (restartcollection*)p;
  {IPCALL(cleargraylists,ipcleargraylists_0,.g = pIp->g);}
  (pIp->g)->GCmarked = 0;
  {markobject(pIp->g, mainthread(pIp->g));}
  {markvalue(pIp->g, &pIp->g->l_registry);}
  {IPCALL(markmt,ipmarkmt_0,.g = pIp->g);}
  {IPCALL(markbeingfnz,ipmarkbeingfnz_0,.g = pIp->g);}  /* mark any finalizing object left from previous cycle */
}