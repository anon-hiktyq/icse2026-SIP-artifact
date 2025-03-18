#include "CheckCal.h"
void CheckCalFun(CheckCal *pIp)
{

	unint32 i;
	unint08 chksum = 0;

	for(i=0; i<pIp -> len; i++)
	{
	    chksum = chksum + pIp -> pkv[i];
	}

	return;
}