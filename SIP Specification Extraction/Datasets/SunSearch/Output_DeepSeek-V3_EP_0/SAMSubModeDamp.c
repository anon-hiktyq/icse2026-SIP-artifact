
#include "TripleFabsMax.h"
#include "SAMSubModeDamp.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->rate + (0..2));
  assigns pIp->countPublic, pIp->flgMode, pIp->countMode, TR32_FLGMODE_VALUE, TR32_BIAS_WYPI_VALUE;
*/
void SAMSubModeDampFun(SAMSubModeDamp *pIp)
{
    float32 fabsmax;
    float32 TripleFabsMax_ret;

    /*@ 
      requires \valid(&TripleFabsMax_ret);
      assigns TripleFabsMax_ret;
    */
    IPCREATE(TripleFabsMax, ipTripleFabsMax, .fx1 = pIp->rate[0], .fy2 = pIp->rate[1], .fz3 = pIp->rate[2], .ret = &(TripleFabsMax_ret));
    IPCALL(ipTripleFabsMax);

    fabsmax = TripleFabsMax_ret;

    /*@ 
      ensures fabsmax == \old(TripleFabsMax_ret);
    */
    if (fabsmax < pIp->max)
    {
        /*@ 
          ensures pIp->countPublic == \old(pIp->countPublic) + 1;
        */
        pIp->countPublic++;
    }

    /*@ 
      ensures (pIp->countPublic > 350 || pIp->countMode > 1000) ==> 
               (pIp->flgMode == SAM_PITCH && pIp->countMode == 0 && pIp->countPublic == 0);
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
