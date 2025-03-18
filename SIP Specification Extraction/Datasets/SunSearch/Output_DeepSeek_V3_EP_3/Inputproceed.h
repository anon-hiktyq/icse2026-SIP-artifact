#if !defined(__INPUTPROCEED_H__)
#define __INPUTPROCEED_H__

#include "common.h"


typedef struct __Inputproceed
{
/* 接口函数 */
	void (*fun)( struct __Inputproceed *);
/* 输入端口 */
	SDSSData			mDSSData;
	/* 输出端口 */
	float32 			VG[9] [3];
	unint08			flgGryoCalc;
	/* 输入输出端口 */
	SAttitude			mAttitude;
	SGyroData			mGyroData;
	/* 状态变量 */
	/* 参数变量 */
} Inputproceed;
void InputproceedFun(Inputproceed *p);
#endif // __INPUTPROCEED_H__