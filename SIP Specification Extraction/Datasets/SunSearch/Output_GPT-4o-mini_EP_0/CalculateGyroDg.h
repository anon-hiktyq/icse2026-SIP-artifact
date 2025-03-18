#if !defined(__CALCULATEGYRODG_H__)
#define __CALCULATEGYRODG_H__

#include "common.h"


typedef struct __CalculateGyroDg
{
/* 接口函数 */
	void (*fun)( struct __CalculateGyroDg *);
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	SGyroData*			pGyroData;
	/* 状态变量 */
	/* 参数变量 */
} CalculateGyroDg;
void CalculateGyroDgFun(CalculateGyroDg *p);
#endif // __CALCULATEGYRODG_H__