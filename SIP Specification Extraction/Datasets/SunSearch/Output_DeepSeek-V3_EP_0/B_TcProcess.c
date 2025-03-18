
#include "CheckCal.h"
#include "B_TcProcess.h"

/*@ axiomatic Sum_array {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
      \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
      \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
   }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->tcaData + (0..3));
    assigns chksum;
    ensures \result == \old(chksum);
*/
void B_TcProcessFun(B_TcProcess *pIp)
{
    unint08 chksum;
    unint08 i;

    /*@ loop invariant 0 <= i <= 3;
        loop assigns chksum;
        loop variant 3 - i;
    */
    for (i = 0; i < 3; i++) {
        // Checksum calculation logic here
    }

    if ((pIp -> tcaData[0] == 0xE1) && (pIp -> tcaData[1] == 0x00))
    {
        IPCREATE(CheckCal, ipCheckCal, .len = 3, .pkv =  &(pIp->tcaData[0]), .chksum =  &chksum);
        IPCALL(ipCheckCal);

        /*@ requires \valid(pIp->tcaData + (0..3));
            ensures \result == (pIp->tcaData[3] == chksum);
        */
        if(pIp -> tcaData[3] == chksum)
        {
            /*@ requires \valid(pIp->tcaData + (0..3));
                ensures \result == (pIp->tcaData[2] == 0 || pIp->tcaData[2] == 1);
            */
            if(pIp -> tcaData[2] == 0)
            {
                TR32_FLGMODE_VALUE(SAM_DAMP);
            }
            else if(pIp -> tcaData[2] == 1)
            {
                TR32_FLGMODE_VALUE(SAM_CRUISE);
            }
            else
            {
                TR32_FLGMODE_VALUE(NOCTRL);
            }
        }
    }

    return;
}
