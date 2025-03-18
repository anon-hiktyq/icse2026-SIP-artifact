#if !defined(__MATRIXTRAN_H__)
#define __MATRIXTRAN_H__

#include "common.h"


typedef struct __MatrixTran
{
/* 接口函数 */
	void (*fun)( struct __MatrixTran *);
/* 输入端口 */
	const float32*			mat;
	unint08			nrow;
	unint08			ncol;
	/* 输出端口 */
	/* 输入输出端口 */
	float32*			tran;
	/* 状态变量 */
	/* 参数变量 */
} MatrixTran;
void MatrixTranFun(MatrixTran *p);
#endif // __MATRIXTRAN_H__