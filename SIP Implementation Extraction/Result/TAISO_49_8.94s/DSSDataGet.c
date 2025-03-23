#include "DSSDataGet.h"
void DSSDataGetFun(void *p) 
{
    DSSDataGet *pIp = (DSSDataGet*)p;

	unint08 si;
	unint08 tmp_ad_start;
	unint08 stateFlag;
	unint16 wd;
	unint16 tmp_hi8, tmp_lo4;

	pIp -> pDSSData->stateFlag_A = 0;
	pIp -> pDSSData->stateFlag_B = 0;

	pIp -> pDSSData->flgSP = (ADDR_READ(0xE000) >> 5) & 0x01 ;	

	/* ��ģ���� */
	for ( si = 0; si < 2; si++ )
	{	
		/* ̫���ӵ�״̬�ɼ� */
		stateFlag = ADDR_READ(0xC000) & 0x3; 				/* ����tmp_ad_start�������ɼ�̫���ӵ�״̬ */
		
		if ((stateFlag & 0x1) == 0x1) 						/* ���� */
		{
			pIp -> pDSSData->stateFlag_A = 1;
		}

		if ((stateFlag & 0x2) == 0x2) 						/* ���� */
		{
			pIp -> pDSSData->stateFlag_B = 1;
		}
	}


	/* ȷ��̫���ӵ��ͨ��AD�ɼ����������Ƕ� */
	if (stateFlag > 0)									
	{
		ADDR_WRITE(0xA100, (0xC + si));							/* ѡ��ͨ�� */
		{IPCALL(Delay,ipDelay_1,.delaytime = 500);}									        	/* 500us,1us���� */
		/* ����ADת�� */
		tmp_ad_start = ADDR_READ(0xA000) ;						/* ����ַ0xA000����ADת�� */
		{IPCALL(Delay,ipDelay_0,.delaytime = 40);}									        	/* 40us,1us���� */
		tmp_lo4 = ADDR_READ(0xA003) ;							/* 0xA003 ��4λ;8λ���ݿ��,��4λ��Ч*/
		tmp_hi8 = ADDR_READ(0xA001) ;							/* 0xA001 ��8λ */
		/* ƴ12λADת������ */
		wd = ((tmp_hi8 << 4) & 0x0FF0 ) | ((tmp_lo4 >> 4) & 0xF) ;
		switch(si)
		{
			case 0:
				pIp -> pDSSData->royaw = DIVIATION_TO_FLOAT_DSS(wd) ;	/* SS1 �����Ƕ� */
				break ;
			case 1:
				pIp -> pDSSData->piyaw = {float32 DiviationToFloat_ret_0;IPCALL(DiviationToFloat,ipDiviationToFloat_0,.input = wd,.ret = &DiviationToFloat_ret_0);};	/* SS2 �����Ƕ� */
				break ;
			default:
				break ;
		}
	}

	return;
}