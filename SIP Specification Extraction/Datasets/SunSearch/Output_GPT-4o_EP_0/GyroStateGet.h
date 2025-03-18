#if !defined(__GYROSTATEGET_H__)
#define __GYROSTATEGET_H__

#include "common.h"


typedef struct __GyroStateGet
{
/* 接口函数 */
	void (*fun)( struct __GyroStateGet *);
/* 输入端口 */
	unint32			NumGyro;
	/* 输出端口 */
	/* 输入输出端口 */
	unint32*			stateFlag;
	float32*			wa;
	/* 状态变量 */
	/* 参数变量 */
} GyroStateGet;
void GyroStateGetFun(GyroStateGet *p);
#endif // __GYROSTATEGET_H__