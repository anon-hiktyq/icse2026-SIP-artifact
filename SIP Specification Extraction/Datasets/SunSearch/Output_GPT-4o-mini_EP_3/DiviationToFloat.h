#if !defined(__DIVIATIONTOFLOAT_H__)
#define __DIVIATIONTOFLOAT_H__

#include "common.h"


typedef struct __DiviationToFloat
{
/* 接口函数 */
	void (*fun)( struct __DiviationToFloat *);
/* 输入端口 */
	unint16			input;
	unint16			mask;
	unint16			offset;
	float32			LSB;
	/* 输出端口 */
	float32			fresult;
	float32*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} DiviationToFloat;
void DiviationToFloatFun(DiviationToFloat *p);
#endif // __DIVIATIONTOFLOAT_H__