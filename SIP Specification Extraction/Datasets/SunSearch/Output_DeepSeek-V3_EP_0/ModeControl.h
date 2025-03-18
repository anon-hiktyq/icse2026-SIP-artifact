#if !defined(__MODECONTROL_H__)
#define __MODECONTROL_H__

#include "common.h"


typedef struct __ModeControl
{
/* 接口函数 */
	void (*fun)( struct __ModeControl *);
/* 输入端口 */
	unint08			Count160ms;
	unint32			countPublic;
	SAttitude			mAttitude;
	SController 			mController[3];
	/* 输出端口 */
	unint16			flgPRSAM;
	/* 输入输出端口 */
	unint32			countMode;
	SDSSData			mDSSData;
	SFWarning			mFWarning;
	/* 状态变量 */
	/* 参数变量 */
} ModeControl;
void ModeControlFun(ModeControl *p);
#endif // __MODECONTROL_H__