#if !defined(__CHECKCAL_H__)
#define __CHECKCAL_H__

#include "common.h"


typedef struct __CheckCal
{
/* 接口函数 */
	void (*fun)( struct __CheckCal *);
/* 输入端口 */
	const unint32			len;
	const unint08*			pkv;
	unint08              chksum;
	/* 输出端口 */
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} CheckCal;
void CheckCalFun(CheckCal *p);
#endif // __CHECKCAL_H__