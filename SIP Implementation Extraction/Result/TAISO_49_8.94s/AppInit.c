#include "AppInit.h"
void AppInitFun(void *p) 
{
    AppInit *pIp = (AppInit*)p;


	/* ������ʼ�� */
    {IPCALL(InitVar,ipInitVar_0);}

    /* �����ӵ� */
	{IPCALL(DevControl,ipDevControl_0);};

    /* �ж����� */
    ADDR_WRITE(0x8083, 0x1);

	return;
}