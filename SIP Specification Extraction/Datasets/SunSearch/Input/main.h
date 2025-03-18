#if !defined(__MAIN_H__)
#define __MAIN_H__

#include "common.h"


typedef struct __main
{
/* 接口函数 */
	void (*fun)( struct __main *);
/* 输入端口 */
	/* 输出端口 */
	SControllerParam 			CTRL_PARAM_SAM[3];
	float32 			VG[9] [3];
	unint08			nouse;
	unint08			countInt32ms;
	unint08			Count160ms;
	unint32			countSate;
	unint32			countPublic;
	unint32			countMode;
	unint16			flgPRSAM;
	unint08			flgGryoCalc;
	unint16			flg160INT;
	SAttitude			mAttitude;
	SDSSData			mDSSData;
	SGyroData			mGyroData;
	SController 			mController[3];
	SFratemodulator 			mModulator[3];
	SThrDistribute			mThrDistribute;
	SFWarning			mFWarning;
	int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} main;
void mainFun(main *p);
#endif // __MAIN_H__