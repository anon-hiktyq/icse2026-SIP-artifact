#if !defined(__TCPROCESS_H__)
#define __TCPROCESS_H__

#include "common.h"


typedef struct __TcProcess
{
/* 接口函数 */
	void (*fun)( struct __TcProcess *);
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} TcProcess;
void TcProcessFun(TcProcess *p);
#endif // __TCPROCESS_H__