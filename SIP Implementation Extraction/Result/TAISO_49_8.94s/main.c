#include "main.h"
void mainFun(void *p) 
{
    main *pIp = (main*)p;


	{IPCALL(AppInit,ipAppInit_0);};												/* ��ʼ�� */

	{IPCALL(PeriodControl,ipPeriodControl_0);}										/* ���ڿ��� */
    *(pIp -> ret) = 0;
}