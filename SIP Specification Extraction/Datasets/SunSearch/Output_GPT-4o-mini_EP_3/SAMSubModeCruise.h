#if !defined(__SAMSUBMODECRUISE_H__)
#define __SAMSUBMODECRUISE_H__

#include "common.h"


typedef struct __SAMSubModeCruise
{
/* 接口函数 */
	void (*fun)( struct __SAMSubModeCruise *);
/* 输入端口 */
	const unint32			countMode;
	/* 输出端口 */
	SFWarning			mFWarning;
	unint08      		Count160ms;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} SAMSubModeCruise;
void SAMSubModeCruiseFun(SAMSubModeCruise *p);
#endif // __SAMSUBMODECRUISE_H__