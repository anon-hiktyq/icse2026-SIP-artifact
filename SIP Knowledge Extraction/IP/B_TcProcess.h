#if !defined(__B_TCPROCESS_H__)
#define __B_TCPROCESS_H__

#include "common.h"


typedef struct __B_TcProcess
{
/* 接口函数 */
	void (*fun)( struct __B_TcProcess *);
/* 输入端口 */
	unint08*			tcaData;
	/* 输出端口 */
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} B_TcProcess;
void B_TcProcessFun(B_TcProcess *p);
#endif // __B_TCPROCESS_H__