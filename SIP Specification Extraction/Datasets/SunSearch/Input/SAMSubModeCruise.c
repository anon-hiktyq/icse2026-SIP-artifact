#include "SAMSubModeCruise.h"
void SAMSubModeCruiseFun(SAMSubModeCruise *pIp)
{

	if (pIp -> countMode == 4000)
	{
		pIp -> mFWarning.CWsp = TRUE ;
	}

	return ;
}