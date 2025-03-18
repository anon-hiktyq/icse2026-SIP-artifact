#if !defined(__TRIPLEFABSMAX_H__)
#define __TRIPLEFABSMAX_H__

#include "common.h"


typedef struct __TripleFabsMax
{
/* 接口函数 */
	void (*fun)( struct __TripleFabsMax *);
/* 输入端口 */
	float32			fx1;
	float32			fy2;
	float32			fz3;
	/* 输出端口 */
	float32			tmax;
	float32*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} TripleFabsMax;
void TripleFabsMaxFun(TripleFabsMax *p);
#endif // __TRIPLEFABSMAX_H__