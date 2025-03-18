#if !defined(__GYROCHOOSE_H__)
#define __GYROCHOOSE_H__

#include "common.h"


typedef struct __GyroChoose
{
/* 接口函数 */
	void (*fun)( struct __GyroChoose *);
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	SGyroData*			pGyroData;
	/* 状态变量 */
	/* 参数变量 */
} GyroChoose;
void GyroChooseFun(GyroChoose *p);
#endif // __GYROCHOOSE_H__