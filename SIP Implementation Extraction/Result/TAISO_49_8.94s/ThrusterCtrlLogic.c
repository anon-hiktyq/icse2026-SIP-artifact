#include "ThrusterCtrlLogic.h"
void ThrusterCtrlLogicFun(void *p) 
{
    ThrusterCtrlLogic *pIp = (ThrusterCtrlLogic*)p;


	if ( pIp -> mModulator[0].Yp != 0)									/* α����״̬�� */
	{
		pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x04 ;	/* ����������� */
	}

	if ( pIp -> mModulator[0].Yn != 0)									/* α����״̬�� */
	{
		pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x08 ;	/* ����������� */
	}

	if ( pIp -> mModulator[1].Yp != 0)									/* α����״̬�� */
	{
		pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x10 ;	/* ����������� */
	}

	if ( pIp -> mModulator[1].Yn != 0)									/* α����״̬�� */
	{
		pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x20 ;	/* ����������� */
	}

	if ( pIp -> mModulator[2].Yp != 0)									/* α����״̬�� */
	{
		pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x40 ;	/* ����������� */
	}

	if ( pIp -> mModulator[2].Yn != 0)									/* α����״̬�� */
	{
		pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x80 ;	/* ����������� */
	}

	return ;
}