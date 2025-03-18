#if !defined(__LIMITCTRLRATEINPUT_H__)
#define __LIMITCTRLRATEINPUT_H__

#include "common.h"


typedef struct __LimitCtrlRateInput
{
/* 接口函数 */
	void (*fun)( struct __LimitCtrlRateInput *);
/* 输入端口 */
	const SAttitude*			pSA;
	const float32			max;
	/* 输出端口 */
	/* 输入输出端口 */
	SController*			pSCtrl;
	/* 状态变量 */
	/* 参数变量 */
} LimitCtrlRateInput;
void LimitCtrlRateInputFun(LimitCtrlRateInput *p);
#endif // __LIMITCTRLRATEINPUT_H__