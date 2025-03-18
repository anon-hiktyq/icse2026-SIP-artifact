
#include "SAMSubModeCruise.h"

/*@ requires pIp != \null; 
    ensures pIp->countMode == 4000 ==> pIp->mFWarning.CWsp == TRUE; 
    ensures pIp->countMode != 4000 ==> pIp->mFWarning.CWsp == \old(pIp->mFWarning.CWsp); 
    assigns pIp->mFWarning.CWsp; */
void SAMSubModeCruiseFun(SAMSubModeCruise *pIp)
{
    if (pIp -> countMode == 4000)
    {
        pIp -> mFWarning.CWsp = TRUE ;
    }

    return ;
}
