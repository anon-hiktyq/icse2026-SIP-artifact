#if !defined(__FAULTJUDGEPROCEED_H__)
#define __FAULTJUDGEPROCEED_H__

#include "common.h"


typedef struct __FaultJudgeProceed
{
/* 接口函数 */
	void (*fun)( struct __FaultJudgeProceed *);
/* 输入端口 */
	/* 输出端口 */
	unint08			nouse;
	unint32			countPublic;
	unint32			countMode;
	SAttitude			mAttitude;
	SDSSData			mDSSData;
	SController 			mController[3];
	/* 输入输出端口 */
	SFWarning			mFWarning;
	/* 状态变量 */
	/* 参数变量 */
} FaultJudgeProceed;
void FaultJudgeProceedFun(FaultJudgeProceed *p);
#endif // __FAULTJUDGEPROCEED_H__