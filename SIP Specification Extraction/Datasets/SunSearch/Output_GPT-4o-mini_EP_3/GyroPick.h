#if !defined(__GYROPICK_H__)
#define __GYROPICK_H__

#include "common.h"


typedef struct __GyroPick
{
/* 接口函数 */
	void (*fun)( struct __GyroPick *);
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	SGyroData*			pGyroData;
	/* 状态变量 */
	/* 参数变量 */
} GyroPick;
void GyroPickFun(GyroPick *p);
#endif // __GYROPICK_H__