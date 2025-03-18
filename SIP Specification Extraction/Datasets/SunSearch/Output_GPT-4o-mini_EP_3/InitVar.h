#if !defined(__INITVAR_H__)
#define __INITVAR_H__

#include "common.h"


typedef struct __InitVar
{
/* 接口函数 */
	void (*fun)( struct __InitVar *);
/* 输入端口 */
	/* 输出端口 */
	unint08			countInt32ms;
	unint32			countSate;
	unint32			countPublic;
	unint32			countMode;
	unint16			flgPRSAM;
	unint08			flgGryoCalc;
	unint16			flg160INT;
	SGyroData			mGyroData;
	SFratemodulator 			mModulator[3];
	SThrDistribute			mThrDistribute;
	SFWarning			mFWarning;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} InitVar;
void InitVarFun(InitVar *p);
#endif // __INITVAR_H__