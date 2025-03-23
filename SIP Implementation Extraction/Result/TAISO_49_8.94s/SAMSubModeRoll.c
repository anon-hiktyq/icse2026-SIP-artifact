#include "SAMSubModeRoll.h"
void SAMSubModeRollFun(void *p) 
{
    SAMSubModeRoll *pIp = (SAMSubModeRoll*)p;

	float32 tmproyaw ;

	if (pIp -> pSDS->flgSP == 0x1)										/* ��SP=1 */
	{
		tmproyaw = ABS(pIp -> pSDS->royaw) ;

		if ( tmproyaw > 1.0f )								/* �޷� */
		{
			pIp -> countPublic++ ;									/* ��ʽ���������� */

			if (pIp -> countPublic > 16)							/* ��ʽ������13=2.08s ��2.048s */
			{
				flgMode = SAM_CRUISE ;
				TR32_FLGMODE_VALUE(flgMode) ;				/* ת��SAMѲ����ʽ */
				TR32_BIAS_WXRO_VALUE(0.0f) ;
				pIp -> countMode = 0 ;								/* �������ڼ����� */
				pIp -> countPublic = 0 ;							/* ��ʽ���������� */
			}
			else
			{
				pIp -> pCtrl[0].Up = 0.0f ;
				pIp -> pCtrl[1].Up = 0.0f ;
				pIp -> pCtrl[2].Up = 0.0f ;
			}
		}
    }
    else
    {
        pIp -> countPublic = 0 ;									/* ��ʽ���������� */
    }


    if (pIp -> countMode > 6250)								    /* ��800s̫���Բ�����,�æ�x=0��/��,��y=-0.5��/��,���¸������� */
    {
		flgMode = SAM_PITCH ;
    	TR32_FLGMODE_VALUE(flgMode) ;						/* ת��SAM����������ʽ */
		TR32_BIAS_WXRO_VALUE(0.0f) ;
		TR32_BIAS_WYPI_VALUE(-0.5f) ;

		pIp -> countMode = 0 ;										/* �������ڼ����� */
		pIp -> countPublic = 0 ;									/* ��ʽ���������� */

		if (pIp -> flgPRSAM == 0x3333)      						/* bPRSFlag = false  ����̫��ʧЧ */
		{
			{IPCALL(SwitchSS,ipSwitchSS_0);};
			pIp -> flgPRSAM = 0xCCCC ;
		}
		else
		{
			pIp -> flgPRSAM = 0x3333 ;

			pIp -> mFWarning.flgups = TRUE ;						/* �ڶ����������ɹ�, ��UPSE */
			pIp -> mFWarning.countUPSpc = 0 ;
        }
    }

	return ;
}