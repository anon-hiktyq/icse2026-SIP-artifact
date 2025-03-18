
#include "SAMSubModeCruise.h"

/*@ 
  requires \valid(pIp);
  ensures pIp->countMode == 4000 ==> pIp->mFWarning.CWsp == TRUE;
  assigns pIp->mFWarning.CWsp;
*/
void SAMSubModeCruiseFun(SAMSubModeCruise *pIp)
{
    /*@ loop invariant pIp->countMode == 4000 ==> pIp->mFWarning.CWsp == TRUE;
        loop assigns pIp->mFWarning.CWsp;
        loop variant 1; // No actual loop, but variant is required for structure
    */
    if (pIp->countMode == 4000)
    {
        pIp->mFWarning.CWsp = TRUE;
    }

    return;
}
