#include "InitVar.h"
void InitVarFun(void *p) 
{
    InitVar *pIp = (InitVar*)p;

	pIp -> flg160INT = 0x3333 ;									/* 160ms�жϱ�־��δ��160ms */
	pIp -> flgPRSAM = 0x3333 ;										/* ����̫��ʧЧ��־�� 0x3333��ʾʧЧ */

	pIp -> mGyroData.gyroStatus0 = 0 ;								/* ����״̬��ǰһ���ڣ� */
	pIp -> mGyroData.gyroStatus1 = 0 ;								/* ����״̬����ǰ���ڣ� */

	/* ��������ʼ�� */
	pIp -> countSate    = 0 ;										/* ��ʱ������ */
	pIp -> countPublic  = 0 ;
	pIp -> countMode    = 0 ;										/* �������ڼ��� */
	pIp -> countInt32ms = 0 ;										/* 32ms������ */

	pIp -> mFWarning.countSPLost = 0 ;								/* SP��ʧ���� */
	pIp -> mFWarning.countSPSeen = 0 ;								/* SP�ɼ����� */
	pIp -> mFWarning.countSPset  = 0 ;								/* ���л�̫�������� */
	pIp -> mFWarning.countUPSpc  = 0 ;

	/* ��ȡ��������ʼ�� */
	TR32_FLGMODE_VALUE(SAM_DAMP) ;							/* Ĭ���������᷽ʽ */
	TR32_BIAS_WXRO_VALUE(0.0f) ;							/* ���ٶ�ƫ�������� */
	TR32_BIAS_WYPI_VALUE(0.0f) ;							/* ���ٶ�ƫ�������� */

	pIp -> mThrDistribute.wPulse = 0x0 ;							/* ��12��10N��������Ӧ����������� */

	/* α����״̬������ */
	pIp -> mModulator[0].r = 0.0f ;
	pIp -> mModulator[1].r = 0.0f ;
	pIp -> mModulator[2].r = 0.0f ;

	pIp -> flgGryoCalc = FALSE ;                                   /* ��ʼ�������ݼ����־ */

	return;
}