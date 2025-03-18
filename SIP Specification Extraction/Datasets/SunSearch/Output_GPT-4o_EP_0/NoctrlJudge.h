#if !defined(__NOCTRLJUDGE_H__)
#define __NOCTRLJUDGE_H__

#include "common.h"


typedef struct __NoctrlJudge
{
/* 接口函数 */
	void (*fun)( struct __NoctrlJudge *);
/* 输入端口 */
	SAttitude			mAttitude;
	/* 输出端口 */
	/* 输入输出端口 */
	unint08			nouse;
	SFWarning			mFWarning;
	/* 状态变量 */
	/* 参数变量 */
} NoctrlJudge;
void NoctrlJudgeFun(NoctrlJudge *p);
#endif // __NOCTRLJUDGE_H__