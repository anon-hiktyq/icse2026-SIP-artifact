
#include "CheckCal.h"
#include "B_TcProcess.h"

/*@ 
  requires pIp != \null; 
  requires \valid(pIp->tcaData + (0..3)); 
  assigns \nothing; 
  ensures \result == 0; 
*/
void B_TcProcessFun(B_TcProcess *pIp)
{
    /*@ 
      requires \valid(pIp->tcaData + (0..3)); 
      assigns chksum, i; 
      ensures \forall integer j; 0 <= j < 3 ==> pIp->tcaData[j] == \old(pIp->tcaData[j]); 
    */
	unint08 chksum;
	unint08 i;

	/*@ 
	  requires \valid(pIp->tcaData + (0..3)); 
	  assigns \nothing; 
	  ensures (pIp->tcaData[0] == 0xE1 && pIp->tcaData[1] == 0x00) ==> 
	    (pIp->tcaData[3] == chksum ==> 
	      (pIp->tcaData[2] == 0 ==> \result == SAM_DAMP) &&
	      (pIp->tcaData[2] == 1 ==> \result == SAM_CRUISE) &&
	      (pIp->tcaData[2] != 0 && pIp->tcaData[2] != 1 ==> \result == NOCTRL));
	*/
	if ((pIp -> tcaData[0] == 0xE1) && (pIp -> tcaData[1] == 0x00))
	{
		IPCREATE(CheckCal, ipCheckCal, .len = 3, .pkv =  &(pIp->tcaData[0]), .chksum =  &chksum);
		IPCALL(ipCheckCal);

	    /*@ 
	      requires \valid(pIp->tcaData + (0..3)); 
	      assigns \nothing; 
	      ensures pIp->tcaData[3] == chksum ==> 
	        (pIp->tcaData[2] == 0 ==> \result == SAM_DAMP) &&
	        (pIp->tcaData[2] == 1 ==> \result == SAM_CRUISE) &&
	        (pIp->tcaData[2] != 0 && pIp->tcaData[2] != 1 ==> \result == NOCTRL);
	    */
	    if(pIp -> tcaData[3] == chksum)
	    {
	    	if(pIp -> tcaData[2] == 0)
	    	{
	    		TR32_FLGMODE_VALUE(SAM_DAMP) ;
	    	}
	    	else if(pIp -> tcaData[2] == 1)
	    	{
	    		TR32_FLGMODE_VALUE(SAM_CRUISE) ;
	    	}
	    	else
	    	{
	    		TR32_FLGMODE_VALUE(NOCTRL) ;
	    	}
	    }
	}

	return;
}
