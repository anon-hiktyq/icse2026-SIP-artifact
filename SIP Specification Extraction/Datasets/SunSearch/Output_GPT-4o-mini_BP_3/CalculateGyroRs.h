#if !defined(__CALCULATEGYRORS_H__)
#define __CALCULATEGYRORS_H__

#include "common.h"


typedef struct __CalculateGyroRs
{
/* 接口函数 */
	void (*fun)( struct __CalculateGyroRs *);
/* 输入端口 */
	float32 			VG[9] [3];
	/* 输出端口 */
	/* 输入输出端口 */
	SGyroData*			pGyroData;
	unint08			flgGryoCalc;
	/* 状态变量 */
	/* 参数变量 */
} CalculateGyroRs;
void CalculateGyroRsFun(CalculateGyroRs *p);
#endif // __CALCULATEGYRORS_H__