#if !defined(__TR32UINT08_H__)
#define __TR32UINT08_H__

#include "common.h"


typedef struct __Tr32Uint08
{
/* 接口函数 */
	void (*fun)( struct __Tr32Uint08 *);
/* 输入端口 */
	unint08*			pC;
	unint08*			pB;
	unint08*			pA;
	/* 输出端口 */
	unint08			uiresult;
	unint08*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} Tr32Uint08;
void Tr32Uint08Fun(Tr32Uint08 *p);
#endif // __TR32UINT08_H__