
#include "TripleFabsMax.h"
#include "SAMSubModeDamp.h"

/*@ axiomatic Sum_array {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
      \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
      \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
   }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->rate + (0..2));
    assigns pIp->countPublic, pIp->flgMode, pIp->countMode;
    ensures pIp->flgMode == \old(pIp->flgMode) || pIp->flgMode == SAM_PITCH;
    ensures pIp->countMode == 0 || pIp->countMode == \old(pIp->countMode);
    ensures pIp->countPublic == 0 || pIp->countPublic == \old(pIp->countPublic) + 1;
*/
void SAMSubModeDampFun(SAMSubModeDamp *pIp)
{
    float32 fabsmax;
    float32 TripleFabsMax_ret;

    /*@ requires \valid(&(TripleFabsMax_ret));
        assigns TripleFabsMax_ret;
    */
    IPCREATE(TripleFabsMax, ipTripleFabsMax, .fx1 =  pIp->rate[0], .fy2 =  pIp->rate[1], .fz3 =  pIp->rate[2] , .ret = &(TripleFabsMax_ret));
    IPCALL(ipTripleFabsMax);

    fabsmax = TripleFabsMax_ret;

    /*@ assigns pIp->countPublic;
        ensures fabsmax < pIp->max ==> pIp->countPublic == \old(pIp->countPublic) + 1;
        ensures fabsmax >= pIp->max ==> pIp->countPublic == \old(pIp->countPublic);
    */
    if (fabsmax < pIp->max)
    {
        pIp->countPublic++;
    }

    /*@ assigns pIp->flgMode, pIp->countMode, pIp->countPublic;
        ensures (pIp->countPublic > 350 || pIp->countMode > 1000) ==> 
                (pIp->flgMode == SAM_PITCH && pIp->countMode == 0 && pIp->countPublic == 0);
        ensures !(pIp->countPublic > 350 || pIp->countMode > 1000) ==> 
                (pIp->flgMode == \old(pIp->flgMode) && pIp->countMode == \old(pIp->countMode) && pIp->countPublic == \old(pIp->countPublic));
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
