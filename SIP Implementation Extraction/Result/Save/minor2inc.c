#include "minor2inc.h"
void minor2incFun(void *p) 
{
    minor2inc *pIp = (minor2inc*)p;
  (pIp->g)->GCmajorminor = (pIp->g)->GCmarked;  /* number of live bytes */
  (pIp->g)->gckind = (pIp->kind);
  (pIp->g)->reallyold = (pIp->g)->old1 = (pIp->g)->survival = NULL;
  (pIp->g)->finobjrold = (pIp->g)->finobjold1 = (pIp->g)->finobjsur = NULL;
  {IPCALL(entersweep,ipentersweep_0,.L = pIp->L);}  /* continue as an incremental cycle */
  /* set a debt equal to the step size */
  {luaE_setdebt(pIp->g, applygcparam(pIp->g, STEPSIZE, 100));}
}