
#include "SAMSubModeCruise.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&(pIp->mFWarning));
  assigns pIp->mFWarning.CWsp;
  ensures pIp->countMode != 4000 || pIp->mFWarning.CWsp == TRUE;
*/
void SAMSubModeCruiseFun(SAMSubModeCruise *pIp)
{
    /*@ 
      requires \valid(pIp);
      requires \valid(&(pIp->mFWarning));
      assigns pIp->mFWarning.CWsp;
      ensures pIp->countMode != 4000 || pIp->mFWarning.CWsp == TRUE;
    */
	if (pIp->countMode == 4000)
	{
		pIp->mFWarning.CWsp = TRUE;
	}

	return;
}
