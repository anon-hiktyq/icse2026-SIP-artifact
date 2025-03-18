#if !defined(__PERIODCONTROL_H__)
#define __PERIODCONTROL_H__

#include "common.h"


typedef struct __PeriodControl
{
/* 接口函数 */
	void (*fun)( struct __PeriodControl *);
/* 输入端口 */
	/* 输出端口 */
	SControllerParam 			CTRL_PARAM_SAM[3];
	float32 			VG[9] [3];
	unint08			nouse;
	unint08			Count160ms;
	unint32			countPublic;
	unint32			countMode;
	unint16			flgPRSAM;
	SAttitude			mAttitude;
	SDSSData			mDSSData;
	SGyroData			mGyroData;
	SController 			mController[3];
	SFratemodulator 			mModulator[3];
	SThrDistribute			mThrDistribute;
	SFWarning			mFWarning;
	/* 输入输出端口 */
	unint32			countSate;
	unint08			flgGryoCalc;
	unint16			flg160INT;
	/* 状态变量 */
	/* 参数变量 */
} PeriodControl;
void PeriodControlFun(PeriodControl *p);
#endif // __PERIODCONTROL_H__