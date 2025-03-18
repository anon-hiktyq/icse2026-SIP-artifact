#if !defined(__TMPROCESS_H__)
#define __TMPROCESS_H__

#include "common.h"


typedef struct __TMProcess
{
/* 接口函数 */
	void (*fun)( struct __TMProcess *);
/* 输入端口 */
	unint32			countSate;
	SAttitude			mAttitude;
	/* 输出端口 */
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} TMProcess;
void TMProcessFun(TMProcess *p);
#endif // __TMPROCESS_H__