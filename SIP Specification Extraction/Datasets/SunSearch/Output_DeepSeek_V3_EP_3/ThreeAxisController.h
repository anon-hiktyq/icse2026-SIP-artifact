#if !defined(__THREEAXISCONTROLLER_H__)
#define __THREEAXISCONTROLLER_H__

#include "common.h"


typedef struct __ThreeAxisController
{
/* 接口函数 */
	void (*fun)( struct __ThreeAxisController *);
/* 输入端口 */
	SControllerParam 			CTRL_PARAM_SAM[3];
	/* 输出端口 */
	SThrDistribute			mThrDistribute;
	/* 输入输出端口 */
	SController 			mController[3];
	SFratemodulator 			mModulator[3];
	/* 状态变量 */
	/* 参数变量 */
} ThreeAxisController;
void ThreeAxisControllerFun(ThreeAxisController *p);
#endif // __THREEAXISCONTROLLER_H__