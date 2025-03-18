#if !defined(__LIMITFLOAT32_H__)
#define __LIMITFLOAT32_H__

#include "common.h"


typedef struct __LimitFloat32
{
/* 接口函数 */
	void (*fun)( struct __LimitFloat32 *);
/* 输入端口 */
	float32			fin;
	float32			fbound;
	/* 输出端口 */
	float32			fvalue;
	float32*			ret;
	SController*			pSCtrl;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} LimitFloat32;
void LimitFloat32Fun(LimitFloat32 *p);
#endif // __LIMITFLOAT32_H__