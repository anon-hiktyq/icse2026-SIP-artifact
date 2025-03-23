#include "checkmajorminor.h"
void checkmajorminorFun(void *p) 
{
    checkmajorminor *pIp = (checkmajorminor*)p;
  if ((pIp->g)->gckind == KGC_GENMAJOR) {  /* generational mode? */
    l_mem numbytes;{numbytes = gettotalbytes(pIp->g);}
    l_mem addedbytes = numbytes - (pIp->g)->GCmajorminor;
    l_mem limit;{limit = applygcparam(pIp->g, MAJORMINOR, addedbytes);}
    l_mem tobecollected = numbytes - (pIp->g)->GCmarked;
    if (tobecollected > limit) {
      {IPCALL(atomic2gen,ipatomic2gen_0,.L = pIp->L,.g = pIp->g);}  /* return to generational mode */
      {IPCALL(setminordebt,ipsetminordebt_0,.g = pIp->g);}
      *(pIp->ret) =  1;  /* exit incremental collection */
    }
  }
  (pIp->g)->GCmajorminor = (pIp->g)->GCmarked;  /* prepare for next collection */
  *(pIp->ret) =  0;  /* stay doing incremental collections */
}