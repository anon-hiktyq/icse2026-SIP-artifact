#include "SoftFaultProceedSP.h"
void SoftFaultProceedSPFun(void *p) 
{
    SoftFaultProceedSP *pIp = (SoftFaultProceedSP*)p;

	pIp -> mFWarning.countSPset++ ;								/* �л�̫���������������̿� */

    switch (pIp -> mFWarning.countSPset)
    {

	    case 5:	    	
	    	
			{IPCALL(SwitchSS,ipSwitchSS_0);};

			break ;

		case 10:

			pIp -> mFWarning.CWsp = FALSE ;
			pIp -> mFWarning.CWtf = FALSE ;						/* �л�SSE��ת��ʽ�����᷽ʽ������CWtf */
			pIp -> mFWarning.countSPset = 0 ;						/* �л�̫�������� */
			pIp -> mFWarning.Wsp = FALSE ;

			/* ���½������� */
			TR32_FLGMODE_VALUE(SAM_DAMP) ;
			TR32_BIAS_WXRO_VALUE(0.0f) ;					/* ����ƫ������ */
			TR32_BIAS_WYPI_VALUE(0.0f) ;					/* ����ƫ������ */
	        pIp -> mController[0].Up = 0.0f ;						/* ��������� */
		    pIp -> mController[1].Up = 0.0f ;						/* ��������� */
		    pIp -> mController[2].Up = 0.0f ;						/* ��������� */

	        pIp -> countMode = 0 ;									/* �������ڼ����� */
	        pIp -> countPublic = 0 ;

			break ;

	    default:
	        break ;
	}

	return ;
}