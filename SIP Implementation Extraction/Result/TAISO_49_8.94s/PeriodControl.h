#if !defined(__PERIODCONTROL_H__)
#define __PERIODCONTROL_H__

#include "common.h"
#include "TcProcess.h"
#include "Input.h"
#include "Inputproceed.h"
#include "ModeControl.h"
#include "LimitControllerInput.h"
#include "ThreeAxisController.h"
#include "FaultJudgeProceed.h"
#include "TMProcess.h"

#ifndef _UNINT08_
	typedef unsigned char   unint08;
#endif

#ifndef _UNINT16_
	typedef unsigned int    unint16;
#endif

#ifndef _UNINT32_
	typedef unsigned long   unint32;
#endif


void PeriodControlFun(void *p);

typedef struct __PeriodControl
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	unint08			nouse;
	unint32			countSate;
	unint32			countPublic;
	unint32			countMode;
	unint16			flgPRSAM;
	unint08			flgGryoCalc;
	unint16			flg160INT;
	SAttitude			mAttitude;
	SGyroData			mGyroData;
	SController 			mController[3];
	SFratemodulator 			mModulator[3];
	SThrDistribute			mThrDistribute;
	SFWarning			mFWarning;
	/* Statement Variables*/
	/* Argument Variables */
	SControllerParam 			CTRL_PARAM_SAM[3];
	float32 			VG[9] [3];
	unint08			Count160ms;
	SDSSData			mDSSData;
} PeriodControl;

#endif // __PERIODCONTROL_H__