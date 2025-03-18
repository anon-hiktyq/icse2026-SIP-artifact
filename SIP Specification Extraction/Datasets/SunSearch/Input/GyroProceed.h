#if !defined(__GYROPROCEED_H__)
#define __GYROPROCEED_H__

#include "common.h"


typedef struct __GyroProceed
{
/* 接口函数 */
	void (*fun)( struct __GyroProceed *);
/* 输入端口 */
	/* 输出端口 */
	float32 			VG[9] [3];
	unint08			flgGryoCalc;
	/* 输入输出端口 */
	SGyroData			mGyroData;
	/* 状态变量 */
	/* 参数变量 */
} GyroProceed;
void GyroProceedFun(GyroProceed *p);
#endif // __GYROPROCEED_H__