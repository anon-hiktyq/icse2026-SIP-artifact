#include "CheckCal16.h"
void CheckCal16Fun(CheckCal16 *pIp)
{

	unint32 i;
	unint16 chksum = 0;
	for(i=0; i<pIp -> len; i++)
	{
	    chksum = chksum + pIp -> pkv[i];
	}
	return;
}