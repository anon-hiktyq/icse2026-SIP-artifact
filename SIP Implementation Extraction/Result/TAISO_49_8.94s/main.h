#if !defined(__MAIN_H__)
#define __MAIN_H__

#include "common.h"
#include "AppInit.h"
#include "PeriodControl.h"



void mainFun(void *p);

typedef struct __main
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	unint08			countInt32ms;
	int*			ret;
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
} main;

#endif // __MAIN_H__