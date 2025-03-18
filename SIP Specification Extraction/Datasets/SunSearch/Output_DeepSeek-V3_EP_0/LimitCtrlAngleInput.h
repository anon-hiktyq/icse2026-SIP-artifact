#if !defined(__LIMITCTRLANGLEINPUT_H__)
#define __LIMITCTRLANGLEINPUT_H__

#include "common.h"


typedef struct __LimitCtrlAngleInput
{
/* 接口函数 */
	void (*fun)( struct __LimitCtrlAngleInput *);
/* 输入端口 */
	const SAttitude*			pSA;
	const float32			max;
	/* 输出端口 */
	/* 输入输出端口 */
	SController*			pSCtrl;
	/* 状态变量 */
	/* 参数变量 */
} LimitCtrlAngleInput;
void LimitCtrlAngleInputFun(LimitCtrlAngleInput *p);
#endif // __LIMITCTRLANGLEINPUT_H__