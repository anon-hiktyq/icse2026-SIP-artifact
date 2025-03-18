#if !defined(__JETDATAGET_H__)
#define __JETDATAGET_H__

#include "common.h"


typedef struct __JetDataGet
{
/* 接口函数 */
	void (*fun)( struct __JetDataGet *);
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	SThrDistribute			mThrDistribute;
	/* 状态变量 */
	/* 参数变量 */
} JetDataGet;
void JetDataGetFun(JetDataGet *p);
#endif // __JETDATAGET_H__