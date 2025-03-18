#if !defined(__THRUSTERCTRLLOGIC_H__)
#define __THRUSTERCTRLLOGIC_H__

#include "common.h"


typedef struct __ThrusterCtrlLogic
{
/* 接口函数 */
	void (*fun)( struct __ThrusterCtrlLogic *);
/* 输入端口 */
	SFratemodulator 			mModulator[3];
	/* 输出端口 */
	/* 输入输出端口 */
	SThrDistribute			mThrDistribute;
	/* 状态变量 */
	/* 参数变量 */
} ThrusterCtrlLogic;
void ThrusterCtrlLogicFun(ThrusterCtrlLogic *p);
#endif // __THRUSTERCTRLLOGIC_H__