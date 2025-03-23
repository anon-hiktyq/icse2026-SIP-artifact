#include "TMProcess.h"
void TMProcessFun(void *p) 
{
    TMProcess *pIp = (TMProcess*)p;

	unint32 tmpSate;
	unint16 chksum;
	unint08 flgModetmp1;
	unint32 i;
	// unint08 flgModetmp1 ;
	unint08 pkv[32];    /* ң������ */

	chksum = 0;

	flgModetmp1 = TR32_FLGMODE() ;				/* ����������ʽ�� */

	for(i = 0; i < 32; i++)
	{
		pkv[i] = 0;
	}

	pkv[0] = 0xD0;		/* �����ͷ */
	pkv[1] = 0xC1;

	/* �����ʱ */
	pkv[2] = UI32_HIHI8(pIp -> countSate);
	pkv[3] = UI32_HILO8(pIp -> countSate);
	pkv[4] = UI32_LOHI8(pIp -> countSate);
	pkv[5] = UI32_LOLO8(pIp -> countSate);

	/* ���ģʽ�� */
	pkv[6] = flgModetmp1;

	/* �����̬�� */
	/* ������̬�� */
	tmpSate = (unint32)(pIp -> mAttitude.angle[0] * 100.0f);
	pkv[7] = UI32_HIHI8(tmpSate);
	pkv[8] = UI32_HILO8(tmpSate);
	pkv[9] = UI32_LOHI8(tmpSate);
	pkv[10] = UI32_LOLO8(tmpSate);

	/* ������̬�� */
	tmpSate = (unint32)(pIp -> mAttitude.angle[1] * 100.0f);
	pkv[11] = UI32_HIHI8(tmpSate);
	pkv[12] = UI32_HILO8(tmpSate);
	pkv[13] = UI32_LOHI8(tmpSate);
	pkv[14] = UI32_LOLO8(tmpSate);

	/* �����̬���ٶ� */
	/* �������ٶ� */
	tmpSate = (unint32)(pIp -> mAttitude.rate[0] * 1000.0f);
	pkv[15] = UI32_HIHI8(tmpSate);
	pkv[16] = UI32_HILO8(tmpSate);
	pkv[17] = UI32_LOHI8(tmpSate);
	pkv[18] = UI32_LOLO8(tmpSate);

	/* �������ٶ� */
	tmpSate = (unint32)(pIp -> mAttitude.rate[1] * 1000.0f);
	pkv[19] = UI32_HIHI8(tmpSate);
	pkv[20] = UI32_HILO8(tmpSate);
	pkv[21] = UI32_LOHI8(tmpSate);
	pkv[22] = UI32_LOLO8(tmpSate);

	/* ƫ�����ٶ� */
	tmpSate = (unint32)(pIp -> mAttitude.rate[2] * 1000.0f);
	pkv[23] = UI32_HIHI8(tmpSate);
	pkv[24] = UI32_HILO8(tmpSate);
	pkv[25] = UI32_LOHI8(tmpSate);
	pkv[26] = UI32_LOLO8(tmpSate);


	{IPCALL(CheckCal16,ipCheckCal16_0,.len = 30,.pkv = &pkv[0],.chksum = &chksum);}

	/* У��ʹ�� */
	pkv[30] = UI16_HI8(chksum);
	pkv[31] = UI16_LO8(chksum);


	{IPCALL(SendUartData,ipSendUartData_0,.data = &pkv[0],.len = 32,.addr = 0x88DB);}


	return;
}