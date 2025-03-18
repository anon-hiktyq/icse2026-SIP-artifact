#if !defined(__DELAY_H__)
#define __DELAY_H__

#include "common.h"


typedef struct __Delay
{
/* 接口函数 */
	void (*fun)( struct __Delay *);
/* 输入端口 */
	unint16			delaytime;
	/* 输出端口 */
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} Delay;
void DelayFun(Delay *p);
#endif // __DELAY_H__