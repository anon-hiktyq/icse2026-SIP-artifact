#if !defined(__DSSDATAGET_H__)
#define __DSSDATAGET_H__

#include "common.h"


typedef struct __DSSDataGet
{
/* 接口函数 */
	void (*fun)( struct __DSSDataGet *);
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	SDSSData*			pDSSData;
	/* 状态变量 */
	/* 参数变量 */
} DSSDataGet;
void DSSDataGetFun(DSSDataGet *p);
#endif // __DSSDATAGET_H__