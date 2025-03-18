#if !defined(__INPUT_H__)
#define __INPUT_H__

#include "common.h"


typedef struct __Input
{
/* 接口函数 */
	void (*fun)( struct __Input *);
/* 输入端口 */
	/* 输出端口 */
	SThrDistribute			mThrDistribute;
	SGyroData               mGyroData;
	SDSSData                mDSSData;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} Input;
void InputFun(Input *p);
#endif // __INPUT_H__