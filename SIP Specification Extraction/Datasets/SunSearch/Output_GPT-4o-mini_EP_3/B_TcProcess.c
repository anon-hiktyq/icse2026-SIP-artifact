
#include "CheckCal.h"
#include "B_TcProcess.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->tcaData + (0..3));
  assigns \nothing;
*/
void B_TcProcessFun(B_TcProcess *pIp)
{
    unint08 chksum;
    unint08 i;

    if ((pIp->tcaData[0] == 0xE1) && (pIp->tcaData[1] == 0x00))
    {
        IPCREATE(CheckCal, ipCheckCal, .len = 3, .pkv = &(pIp->tcaData[0]), .chksum = &chksum);
        IPCALL(ipCheckCal);

        /*@ 
          requires \valid(pIp);
          requires \valid(pIp->tcaData + (0..3));
          ensures pIp->tcaData[3] == chksum ==> 
              (pIp->tcaData[2] == 0 ==> \true) &&
              (pIp->tcaData[2] == 1 ==> \true) &&
              (pIp->tcaData[2] != 0 && pIp->tcaData[2] != 1 ==> \true);
        */
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
