#if !defined(__MATRIXINV33F_H__)
#define __MATRIXINV33F_H__

#include "common.h"


typedef struct __MatrixInv33F
{
/* 接口函数 */
	void (*fun)( struct __MatrixInv33F *);
/* 输入端口 */
	const float32*			src;
	/* 输出端口 */
	unint08			bAbleInv;
	unint08*			ret;
	/* 输入输出端口 */
	float32*			inv;
	/* 状态变量 */
	/* 参数变量 */
} MatrixInv33F;
void MatrixInv33FFun(MatrixInv33F *p);
#endif // __MATRIXINV33F_H__