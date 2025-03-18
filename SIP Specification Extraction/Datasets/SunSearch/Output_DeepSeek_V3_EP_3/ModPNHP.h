#if !defined(__MODPNHP_H__)
#define __MODPNHP_H__

#include "common.h"


typedef struct __ModPNHP
{
/* 接口函数 */
	void (*fun)( struct __ModPNHP *);
/* 输入端口 */
	float32			x;
	float32			halfperiod;
	/* 输出端口 */
	float32			npp2;
	float32*			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} ModPNHP;
void ModPNHPFun(ModPNHP *p);
#endif // __MODPNHP_H__