#include "CheckCal.h"
void CheckCalFun(void *p) 
{
    CheckCal *pIp = (CheckCal*)p;

	unint32 i;
	chksum = 0;

	for(i=0; i<pIp -> len; i++)
	{
	    chksum = chksum + pIp -> pkv[i];
	}

	return;
}