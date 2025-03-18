#if !defined(__SAMSUBMODEDAMP_H__)
#define __SAMSUBMODEDAMP_H__

#include "common.h"


typedef struct __SAMSubModeDamp
{
/* 接口函数 */
	void (*fun)( struct __SAMSubModeDamp *);
/* 输入端口 */
	const float32*			rate;
	const float32			max;
	unint32			countPublic;
	unint32			countMode;
	unint32         flgMode;
	/* 输出端口 */
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} SAMSubModeDamp;
void SAMSubModeDampFun(SAMSubModeDamp *p);
#endif // __SAMSUBMODEDAMP_H__