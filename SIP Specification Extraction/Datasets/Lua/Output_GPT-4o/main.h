#if !defined(__MAIN_H__)
#define __MAIN_H__

#include "common.h"
#include "funa.h"


typedef struct __main
{
/* 接口函数 */
	void (*fun)( struct __main *);
/* 输入端口 */
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} main;

void mainFun(main *pIp);
#endif // __MAIN_H__