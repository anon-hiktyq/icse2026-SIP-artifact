
#include "CheckCal.h"
#include "B_TcProcess.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->tcaData + (0..3));
  assigns pIp->tcaData[0..3];
*/
void B_TcProcessFun(B_TcProcess *pIp)
{
    unint08 chksum;
    unint08 i;

    /*@ 
      loop invariant 0 <= i <= 3;
      loop assigns i;
      loop variant 3 - i;
    */
    for (i = 0; i < 3; i++) {
        // Loop body (if any)
    }

    if ((pIp->tcaData[0] == 0xE1) && (pIp->tcaData[1] == 0x00))
    {
        /*@ 
          requires \valid(&chksum);
          assigns chksum;
        */
        IPCREATE(CheckCal, ipCheckCal, .len = 3, .pkv = &(pIp->tcaData[0]), .chksum = &chksum);
        IPCALL(ipCheckCal);

        if (pIp->tcaData[3] == chksum)
        {
            if (pIp->tcaData[2] == 0)
            {
                TR32_FLGMODE_VALUE(SAM_DAMP);
            }
            else if (pIp->tcaData[2] == 1)
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
