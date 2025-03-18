#if !defined(__SWITCHSS_H__)
#define __SWITCHSS_H__

#include "common.h"


typedef struct __SwitchSS
{
/* 接口函数 */
	void (*fun)( struct __SwitchSS *);
/* 输入端口 */
	SDSSData			mDSSData;
	/* 输出端口 */
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} SwitchSS;
void SwitchSSFun(SwitchSS *p);
#endif // __SWITCHSS_H__