
#include "SAMSubModeCruise.h"

/*@ 
  requires \valid(pIp);
  assigns pIp->mFWarning.CWsp;
*/
void SAMSubModeCruiseFun(SAMSubModeCruise *pIp)
{
    if (pIp->countMode == 4000)
    {
        pIp->mFWarning.CWsp = TRUE;
    }

    return;
}
