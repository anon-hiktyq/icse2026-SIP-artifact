#include "atomic2gen.h"
void atomic2genFun(void *p) 
{
    atomic2gen *pIp = (atomic2gen*)p;
  {IPCALL(cleargraylists,ipcleargraylists_0,.g = pIp->g);}
  /* sweep all elements making them old */
  (pIp->g)->gcstate = GCSswpallgc;
  {IPCALL(sweep2old,ipsweep2old_0,.L = pIp->L,.p = &g->allgc);}
  /* everything alive now is old */
  (pIp->g)->reallyold = (pIp->g)->old1 = (pIp->g)->survival = (pIp->g)->allgc;
  (pIp->g)->firstold1 = NULL;  /* there are no OLD1 objects anywhere */

  /* repeat for 'finobj' lists */
  {IPCALL(sweep2old,ipsweep2old_1,.L = pIp->L,.p = &g->finobj);}
  (pIp->g)->finobjrold = (pIp->g)->finobjold1 = (pIp->g)->finobjsur = (pIp->g)->finobj;

  {IPCALL(sweep2old,ipsweep2old_2,.L = pIp->L,.p = &g->tobefnz);}

  (pIp->g)->gckind = KGC_GENMINOR;
  (pIp->g)->GCmajorminor = (pIp->g)->GCmarked;  /* "base" for number of bytes */
  (pIp->g)->GCmarked = 0;  /* to count the number of added old1 bytes */
  {IPCALL(finishgencycle,ipfinishgencycle_0,.L = pIp->L,.g = pIp->g);}
}