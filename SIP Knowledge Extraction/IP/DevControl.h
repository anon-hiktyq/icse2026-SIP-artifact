#if !defined(__DEVCONTROL_H__)
#define __DEVCONTROL_H__

#include "common.h"


typedef struct __DevControl
{
/* 接口函数 */
	void (*fun)( struct __DevControl *);
/* 输入端口 */
	/* 输出端口 */
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} DevControl;
void DevControlFun(DevControl *p);
#endif // __DEVCONTROL_H__