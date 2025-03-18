#if !defined(__FUNA_H__)
#define __FUNA_H__

#include "common.h"





typedef struct __funa
{
/* 接口函数 */
	void (*fun)( struct __funa *);
/* 输入端口 */
	int			y;
	/* 输出端口 */
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} funa;

void funaFun(funa *pIp);
#endif // __FUNA_H__