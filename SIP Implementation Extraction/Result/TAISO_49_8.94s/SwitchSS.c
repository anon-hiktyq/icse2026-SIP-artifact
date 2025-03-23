#include "SwitchSS.h"
void SwitchSSFun(void *p) 
{
    SwitchSS *pIp = (SwitchSS*)p;

    /* A�ѿ�  */
    if (pIp -> mDSSData.stateFlag_A == 1)
    {
        /* ��SSE����/��SSE���� */		
		ADDR_WRITE(0x8000,0x2);
    }
    else
    {
        /* ��SSE����/��SSE���� */		
		ADDR_WRITE(0x8000,0x1);
    }

    return ;
}