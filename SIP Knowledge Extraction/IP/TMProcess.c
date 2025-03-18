#include "CheckCal16.h"
#include "Tr32Uint08.h"
#include "SendUartData.h"
#include "TMProcess.h"
void TMProcessFun(void *p)
{
    TMProcess *pIp = (TMProcess*)p;

	unint32 tmpSate;
	unint16 chksum;
	unint08 flgModetmp1;
	unint32 i;

	unint08 pkv[32];

	chksum = 0;

	unint08 Tr32Uint08_ret;
	IPCREATE(Tr32Uint08, ipTr32Uint08, .pA = 0 , .ret = &(Tr32Uint08_ret));
	IPCALL(ipTr32Uint08);

	flgModetmp1 = Tr32Uint08_ret;

	for(i = 0; i < 32; i++)
	{
		pkv[i] = 0;
	}

	pkv[0] = 0xD0;
	pkv[1] = 0xC1;

	pkv[2] = UI32_HIHI8(pIp -> countSate);
	pkv[3] = UI32_HILO8(pIp -> countSate);
	pkv[4] = UI32_LOHI8(pIp -> countSate);
	pkv[5] = UI32_LOLO8(pIp -> countSate);

	pkv[6] = flgModetmp1;

	tmpSate = (unint32)(pIp -> mAttitude.angle[0] * 100.0f);
	pkv[7] = UI32_HIHI8(tmpSate);
	pkv[8] = UI32_HILO8(tmpSate);
	pkv[9] = UI32_LOHI8(tmpSate);
	pkv[10] = UI32_LOLO8(tmpSate);

	tmpSate = (unint32)(pIp -> mAttitude.angle[1] * 100.0f);
	pkv[11] = UI32_HIHI8(tmpSate);
	pkv[12] = UI32_HILO8(tmpSate);
	pkv[13] = UI32_LOHI8(tmpSate);
	pkv[14] = UI32_LOLO8(tmpSate);

	tmpSate = (unint32)(pIp -> mAttitude.rate[0] * 1000.0f);
	pkv[15] = UI32_HIHI8(tmpSate);
	pkv[16] = UI32_HILO8(tmpSate);
	pkv[17] = UI32_LOHI8(tmpSate);
	pkv[18] = UI32_LOLO8(tmpSate);

	tmpSate = (unint32)(pIp -> mAttitude.rate[1] * 1000.0f);
	pkv[19] = UI32_HIHI8(tmpSate);
	pkv[20] = UI32_HILO8(tmpSate);
	pkv[21] = UI32_LOHI8(tmpSate);
	pkv[22] = UI32_LOLO8(tmpSate);

	tmpSate = (unint32)(pIp -> mAttitude.rate[2] * 1000.0f);
	pkv[23] = UI32_HIHI8(tmpSate);
	pkv[24] = UI32_HILO8(tmpSate);
	pkv[25] = UI32_LOHI8(tmpSate);
	pkv[26] = UI32_LOLO8(tmpSate);

	IPCREATE(CheckCal16, ipCheckCal16, .len = 30, .pkv =  &pkv[0], .chksum =  &chksum);
	IPCALL(ipCheckCal16);

	pkv[30] = UI16_HI8(chksum);
	pkv[31] = UI16_LO8(chksum);

	IPCREATE(SendUartData, ipSendUartData, .data = &pkv[0], .len =  32, .addr =  0x88DB);
	IPCALL(ipSendUartData);

	return;
}