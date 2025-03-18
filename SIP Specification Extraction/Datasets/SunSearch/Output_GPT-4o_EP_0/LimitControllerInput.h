#if !defined(__LIMITCONTROLLERINPUT_H__)
#define __LIMITCONTROLLERINPUT_H__

#include "common.h"


typedef struct __LimitControllerInput
{
/* 接口函数 */
	void (*fun)( struct __LimitControllerInput *);
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	SAttitude mAttitude;
	SController mController[3];
	/* 状态变量 */
	/* 参数变量 */
} LimitControllerInput;
void LimitControllerInputFun(LimitControllerInput *p);
#endif // __LIMITCONTROLLERINPUT_H__