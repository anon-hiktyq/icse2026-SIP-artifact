#include "CheckCal16.h"
void CheckCal16Fun(void *p)
{
    CheckCal16 *pIp = (CheckCal16*)p;

	unint32 i;
	unint16 chksum = 0;
	for(i=0; i<pIp -> len; i++)
	{
	    chksum = chksum + pIp -> pkv[i];
	}
	return;
}