#include "SAMSubModeCruise.h"
void SAMSubModeCruiseFun(void *p)
{
    SAMSubModeCruise *pIp = (SAMSubModeCruise*)p;

	if (pIp -> countMode == 4000)
	{
		pIp -> mFWarning.CWsp = TRUE ;
	}

	return ;
}