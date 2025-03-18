#if !defined(__MATRIXMULTI_H__)
#define __MATRIXMULTI_H__

#include "common.h"


typedef struct __MatrixMulti
{
/* 接口函数 */
	void (*fun)( struct __MatrixMulti *);
/* 输入端口 */
	const float32*			multiplier;
	unint08			nrow;
	unint08			nrc;
	unint08			ncol;
	/* 输出端口 */
	/* 输入输出端口 */
	float32*			product;
	const float32*			faciend;
	/* 状态变量 */
	/* 参数变量 */
} MatrixMulti;
void MatrixMultiFun(MatrixMulti *p);
#endif // __MATRIXMULTI_H__