
#include "TripleFabsMax.h"
#include "SAMSubModeDamp.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->rate + (0..2));
  requires pIp->countPublic >= 0;
  requires pIp->countMode >= 0;
  requires pIp->max >= 0;
  assigns pIp->countPublic, pIp->countMode, pIp->flgMode;
  ensures pIp->countPublic == \old(pIp->countPublic) + (\exists float32 f; f == \old(TripleFabsMax_ret) && f < pIp->max ? 1 : 0);
*/
void SAMSubModeDampFun(SAMSubModeDamp *pIp)
{
    float32 fabsmax;
    float32 TripleFabsMax_ret;

    /*@ 
      requires \valid(pIp);
      requires \valid(pIp->rate + (0..2));
      assigns TripleFabsMax_ret;
    */
    IPCREATE(TripleFabsMax, ipTripleFabsMax, .fx1 =  pIp->rate[0], .fy2 =  pIp->rate[1], .fz3 =  pIp->rate[2], .ret = &(TripleFabsMax_ret));
    IPCALL(ipTripleFabsMax);

    fabsmax = TripleFabsMax_ret;

    /*@ 
      assigns pIp->countPublic;
      ensures pIp->countPublic == \old(pIp->countPublic) + (fabsmax < pIp->max ? 1 : 0);
    */
    if (fabsmax < pIp->max)
    {
        pIp->countPublic++;
    }

    /*@ 
      assigns pIp->flgMode, pIp->countMode, pIp->countPublic;
      ensures pIp->countPublic >= 0 && pIp->countMode >= 0;
    */
    if ((pIp->countPublic > 350) || (pIp->countMode > 1000))
    {
        pIp->flgMode = SAM_PITCH;
        TR32_FLGMODE_VALUE(pIp->flgMode);
        TR32_BIAS_WYPI_VALUE(-0.5f);

        pIp->countMode = 0;
        pIp->countPublic = 0;
    }

    return;
}
