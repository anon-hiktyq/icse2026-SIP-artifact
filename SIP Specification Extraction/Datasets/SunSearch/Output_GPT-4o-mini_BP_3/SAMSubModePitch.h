#if !defined(__SAMSUBMODEPITCH_H__)
#define __SAMSUBMODEPITCH_H__

#include "common.h"


typedef struct __SAMSubModePitch
{
/* 接口函数 */
	void (*fun)( struct __SAMSubModePitch *);
/* 输入端口 */
	const SDSSData*			pSDS;
	unint32			countPublic;
	unint32			countMode;
	unint32         flgMode;
	/* 输出端口 */
	/* 输入输出端口 */
	SController*			pCtrl;
	/* 状态变量 */
	/* 参数变量 */
} SAMSubModePitch;
void SAMSubModePitchFun(SAMSubModePitch *p);
#endif // __SAMSUBMODEPITCH_H__