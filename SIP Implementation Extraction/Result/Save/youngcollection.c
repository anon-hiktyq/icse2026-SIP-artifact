#include "youngcollection.h"
void youngcollectionFun(void *p) 
{
    youngcollection *pIp = (youngcollection*)p;
  l_mem addedold1 = 0;
  l_mem marked = (pIp->g)->GCmarked;  /* preserve 'g->GCmarked' */
  GCObject **psurvival;  /* to point to first non-dead survival object */
  GCObject *dummy;  /* dummy out parameter to 'sweepgen' */
  {lua_assert(pIp->g->gcstate == GCSpropagate);}
  if ((pIp->g)->firstold1) {  /* are there regular OLD1 objects? */
    {IPCALL(markold,ipmarkold_0,.g = pIp->g,.from = g->firstold1,.to = g->reallyold);}  /* mark them */
    (pIp->g)->firstold1 = NULL;  /* no more OLD1 objects (for now) */
  }
  {IPCALL(markold,ipmarkold_1,.g = pIp->g,.from = g->finobj,.to = g->finobjrold);}
  {IPCALL(markold,ipmarkold_2,.g = pIp->g,.from = g->tobefnz,.to = NULL);}

  {IPCALL(atomic,ipatomic_0,.L = pIp->L);}  /* will lose 'g->marked' */

  /* sweep nursery and get a pointer to its last live element */
  (pIp->g)->gcstate = GCSswpallgc;
  {GCObject ** sweepgen_ret_0;IPCALL(sweepgen,ipsweepgen_0,.L = pIp->L,.g = pIp->g,.p = &g->allgc,.limit = g->survival,.pfirstold1 = &g->firstold1,.paddedold = &addedold1,.ret = sweepgen_ret_0);psurvival = sweepgen_ret_0;}
  /* sweep 'survival' */
  {GCObject ** sweepgen_ret_1;IPCALL(sweepgen,ipsweepgen_1,.L = pIp->L,.g = pIp->g,.p = psurvival,.limit = g->old1,.pfirstold1 = &g->firstold1,.paddedold = &addedold1,.ret = sweepgen_ret_1);sweepgen_ret_1;}
  (pIp->g)->reallyold = (pIp->g)->old1;
  (pIp->g)->old1 = *psurvival;  /* 'survival' survivals are old now */
  (pIp->g)->survival = (pIp->g)->allgc;  /* all news are survivals */

  /* repeat for 'finobj' lists */
  dummy = NULL;  /* no 'firstold1' optimization for 'finobj' lists */
  {GCObject ** sweepgen_ret_2;IPCALL(sweepgen,ipsweepgen_2,.L = pIp->L,.g = pIp->g,.p = &g->finobj,.limit = g->finobjsur,.pfirstold1 = &dummy,.paddedold = &addedold1,.ret = sweepgen_ret_2);psurvival = sweepgen_ret_2;}
  /* sweep 'survival' */
  {GCObject ** sweepgen_ret_3;IPCALL(sweepgen,ipsweepgen_3,.L = pIp->L,.g = pIp->g,.p = psurvival,.limit = g->finobjold1,.pfirstold1 = &dummy,.paddedold = &addedold1,.ret = sweepgen_ret_3);sweepgen_ret_3;}
  (pIp->g)->finobjrold = (pIp->g)->finobjold1;
  (pIp->g)->finobjold1 = *psurvival;  /* 'survival' survivals are old now */
  (pIp->g)->finobjsur = (pIp->g)->finobj;  /* all news are survivals */

  {GCObject ** sweepgen_ret_4;IPCALL(sweepgen,ipsweepgen_4,.L = pIp->L,.g = pIp->g,.p = &g->tobefnz,.limit = NULL,.pfirstold1 = &dummy,.paddedold = &addedold1,.ret = sweepgen_ret_4);sweepgen_ret_4;}

  /* keep total number of added old1 bytes */
  (pIp->g)->GCmarked = marked + addedold1;

  /* decide whether to shift to major mode */
  {int checkminormajor_ret_0;IPCALL(checkminormajor,ipcheckminormajor_0,.g = pIp->g,.ret = &checkminormajor_ret_0);if (checkminormajor_ret_0) {
    {IPCALL(minor2inc,ipminor2inc_0,.L = pIp->L,.g = pIp->g,.kind = KGC_GENMAJOR);}  /* go to major mode */
    (pIp->g)->GCmarked = 0;  /* avoid pause in first major cycle (see 'setpause') */
  }
  else
    {IPCALL(finishgencycle,ipfinishgencycle_0,.L = pIp->L,.g = pIp->g);}}  /* still in minor mode; finish it */
}