#if !defined(__APPINIT_H__)
#define __APPINIT_H__

#include "common.h"
#include "InitVar.h"
#include "DevControl.h"



void AppInitFun(void *p);

typedef struct __AppInit
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	unint08			countInt32ms;
	unint32			countSate;
	unint32			countPublic;
	unint32			countMode;
	unint16			flgPRSAM;
	unint08			flgGryoCalc;
	unint16			flg160INT;
	SGyroData			mGyroData;
	SFratemodulator 			mModulator[3];
	SThrDistribute			mThrDistribute;
	SFWarning			mFWarning;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} AppInit;

#endif // __APPINIT_H__