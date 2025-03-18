#if !defined(__THRABAUTOCHOOSE_H__)
#define __THRABAUTOCHOOSE_H__

#include "common.h"


typedef struct __ThrABAutoChoose
{
/* 接口函数 */
	void (*fun)( struct __ThrABAutoChoose *);
/* 输入端口 */
	/* 输出端口 */
	SThrDistribute			mThrDistribute;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} ThrABAutoChoose;
void ThrABAutoChooseFun(ThrABAutoChoose *p);
#endif // __THRABAUTOCHOOSE_H__