#if !defined(__CHECKCAL16_H__)
#define __CHECKCAL16_H__

#include "common.h"


typedef struct __CheckCal16
{
/* 接口函数 */
	void (*fun)( struct __CheckCal16 *);
/* 输入端口 */
	const unint32			len;
	const unint08*			pkv;

	unint16              chksum;
	/* 输出端口 */
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} CheckCal16;
void CheckCal16Fun(CheckCal16 *p);
#endif // __CHECKCAL16_H__