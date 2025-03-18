#if !defined(__SOFTFAULTJUDGESP_H__)
#define __SOFTFAULTJUDGESP_H__

#include "common.h"


typedef struct __SoftFaultJudgeSP
{
/* 接口函数 */
	void (*fun)( struct __SoftFaultJudgeSP *);
/* 输入端口 */
	SDSSData			mDSSData;
	/* 输出端口 */
	/* 输入输出端口 */
	SFWarning			mFWarning;
	/* 状态变量 */
	/* 参数变量 */
} SoftFaultJudgeSP;
void SoftFaultJudgeSPFun(SoftFaultJudgeSP *p);
#endif // __SOFTFAULTJUDGESP_H__