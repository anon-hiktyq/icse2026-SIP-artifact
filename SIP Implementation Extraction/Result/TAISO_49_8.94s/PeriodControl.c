#include "PeriodControl.h"
void PeriodControlFun(void *p) 
{
    PeriodControl *pIp = (PeriodControl*)p;

	do														/* ��������ѭ��160ms */
	{
		{IPCALL(TcProcess,ipTcProcess_0);}										/* ң��ָ��ɼ������� */

		{IPCALL(Input,ipInput_0);};											/* ���ݲɼ� */

		{IPCALL(Inputproceed,ipInputproceed_0);};									/* ������1 �������ݴ��� 2 ��̬�Ǻͽ��ٶȸ�ֵ  */

		{IPCALL(ModeControl,ipModeControl_0);};										/* ģʽ���� */

		{IPCALL(LimitControllerInput,ipLimitControllerInput_0);};							/* �ڽ������������֮ǰ����Ҫ����������������޷����� */

		{IPCALL(ThreeAxisController,ipThreeAxisController_0);};								/* ������ģ�� */

		{IPCALL(FaultJudgeProceed,ipFaultJudgeProceed_0);};								/* �����жϺʹ��� */

		pIp -> flgGryoCalc = FALSE  ;								/* �������������ݼ����־ */

		pIp -> countSate++ ;										/* ��ʱ������ */

		if (pIp -> countSate > 0xFFFFFFF0)							/* ��ʱ������ */
		{
			pIp -> countSate = 4000 ;
		}

		/* ���������ң������ */
		{IPCALL(TMProcess,ipTMProcess_0);}

		/* �ж�160ms��ʱ����־ */
		while (pIp -> flg160INT != 0xCCCC)							/* 160ms��ʱʱ��δ�� */
		{
			;
		}

		/* ���ж϶�ʱ��־ */
		pIp -> flg160INT = 0x3333 ;								/* ��160ms��־����һ��160ms������ʼ */

	} while(1) ;

	return;
}