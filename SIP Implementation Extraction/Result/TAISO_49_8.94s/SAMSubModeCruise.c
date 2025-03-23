#include "SAMSubModeCruise.h"
void SAMSubModeCruiseFun(void *p) 
{
    SAMSubModeCruise *pIp = (SAMSubModeCruise*)p;




	if (pIp -> countMode == 4000)									/* ����ģʽ4000���ڣ�512s */
	{
		pIp -> mFWarning.CWsp = TRUE ;								/* ����SP���� */
	}

	return ;
}