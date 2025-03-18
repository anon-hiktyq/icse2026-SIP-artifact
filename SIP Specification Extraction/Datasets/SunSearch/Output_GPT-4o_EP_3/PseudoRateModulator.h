#if !defined(__PSEUDORATEMODULATOR_H__)
#define __PSEUDORATEMODULATOR_H__

#include "common.h"


typedef struct __PseudoRateModulator
{
/* 接口函数 */
	void (*fun)( struct __PseudoRateModulator *);
/* 输入端口 */
	float32			h1;
	/* 输出端口 */
	/* 输入输出端口 */
	SFratemodulator*			pModulator;
	/* 状态变量 */
	/* 参数变量 */
} PseudoRateModulator;
void PseudoRateModulatorFun(PseudoRateModulator *p);
#endif // __PSEUDORATEMODULATOR_H__