
#include "TripleFabsMax.h"
#include "SAMSubModeDamp.h"

/*@ 
  requires pIp != NULL;
  requires \valid(pIp);
  requires \valid(pIp->rate + (0..2));
  requires \valid(&pIp->countPublic);
  requires \valid(&pIp->countMode);
  requires \valid(&pIp->flgMode);
  requires pIp->max >= 0;

  assigns pIp->countPublic, pIp->countMode, pIp->flgMode;

  ensures pIp->countPublic >= 0;
  ensures pIp->countMode >= 0;
  ensures (fabsmax < pIp->max ==> pIp->countPublic == \old(pIp->countPublic) + 1);
  ensures ((pIp->countPublic > 350) || (pIp->countMode > 1000) ==> 
           (pIp->flgMode == SAM_PITCH && pIp->countMode == 0 && pIp->countPublic == 0));
*/
void SAMSubModeDampFun(SAMSubModeDamp *pIp)
{
    float32 fabsmax;

    float32 TripleFabsMax_ret;
    IPCREATE(TripleFabsMax, ipTripleFabsMax, .fx1 =  pIp->rate[0], .fy2 =  pIp->rate[1], .fz3 =  pIp->rate[2] , .ret = &(TripleFabsMax_ret));
    IPCALL(ipTripleFabsMax);

    fabsmax = TripleFabsMax_ret;

    if ( fabsmax < pIp -> max )
    {
        pIp -> countPublic++ ;
    }

    if (( pIp -> countPublic > 350 ) || ( pIp -> countMode > 1000 ))
    {
        pIp->flgMode = SAM_PITCH ;
        TR32_FLGMODE_VALUE(pIp->flgMode) ;
        TR32_BIAS_WYPI_VALUE(-0.5f) ;

        pIp -> countMode = 0 ;
        pIp -> countPublic = 0 ;
    }

    return ;
}
