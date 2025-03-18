#if !defined(__SAMSUBMODEROLL_H__)
#define __SAMSUBMODEROLL_H__

#include "common.h"


typedef struct __SAMSubModeRoll
{
/* 接口函数 */
	void (*fun)( struct __SAMSubModeRoll *);
/* 输入端口 */
	const SDSSData*			pSDS;
	unint32			countPublic;
	unint32			countMode;
	unint32         flgMode;
	/* 输出端口 */
	SDSSData			mDSSData;
	/* 输入输出端口 */
	SController*			pCtrl;
	unint16			flgPRSAM;
	SFWarning			mFWarning;
	/* 状态变量 */
	/* 参数变量 */
} SAMSubModeRoll;
void SAMSubModeRollFun(SAMSubModeRoll *p);
#endif // __SAMSUBMODEROLL_H__