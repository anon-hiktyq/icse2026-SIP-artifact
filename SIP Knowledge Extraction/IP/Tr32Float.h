#if !defined(__TR32FLOAT_H__)
#define __TR32FLOAT_H__

#include "common.h"


typedef struct __Tr32Float
{
/* 接口函数 */
	void (*fun)( struct __Tr32Float *);
/* 输入端口 */
	float32*			pA;
	float32*			pB;
	float32*			pC;
	/* 输出端口 */
	UDTConvert			ui2f;
	float32*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} Tr32Float;
void Tr32FloatFun(Tr32Float *p);
#endif // __TR32FLOAT_H__