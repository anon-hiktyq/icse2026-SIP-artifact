#if !defined(__SOFTFAULTPROCEEDSP_H__)
#define __SOFTFAULTPROCEEDSP_H__

#include "common.h"


typedef struct __SoftFaultProceedSP
{
/* 接口函数 */
	void (*fun)( struct __SoftFaultProceedSP *);
/* 输入端口 */
	/* 输出端口 */
	SDSSData			mDSSData;
	SFWarning			mFWarning;
	/* 输入输出端口 */
	unint32			countPublic;
	unint32			countMode;
	SController 			mController[3];
	/* 状态变量 */
	/* 参数变量 */
} SoftFaultProceedSP;
void SoftFaultProceedSPFun(SoftFaultProceedSP *p);
#endif // __SOFTFAULTPROCEEDSP_H__