#include "CheckCal.h"
void CheckCalFun(void *p)
{
    CheckCal *pIp = (CheckCal*)p;

	unint32 i;
	unint08 chksum = 0;

	for(i=0; i<pIp -> len; i++)
	{
	    chksum = chksum + pIp -> pkv[i];
	}

	return;
}