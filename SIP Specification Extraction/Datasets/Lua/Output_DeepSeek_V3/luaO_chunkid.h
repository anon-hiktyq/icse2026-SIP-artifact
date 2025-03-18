#if !defined(__LUAO_CHUNKID_H__)
#define __LUAO_CHUNKID_H__

#include "common.h"

#define LUA_IDSIZE      60        // 块ID最大长度

/* 字符串处理宏 */
#define PRE             "[string \""   // 字符串前缀
#define POS             "\"]"          // 字符串后缀
#define RETS            "..."          // 截断标记




#ifndef _LL_
	#define LL(x) (sizeof(x)/sizeof(char) - 1)
#endif

#ifndef _CT_DIFF2SZ_
	#define ct_diff2sz(df) ((size_t)(df))
#endif

#ifndef _ADDSTR_
	#define addstr(a,b,l) ( memcpy(a,b,(l) * sizeof(char)), a += (l) )
#endif



typedef struct __luaO_chunkid
{
/* 接口函数 */
	void (*fun)( struct __luaO_chunkid *);
/* 输入端口 */
	size_t			srclen;
	/* 输出端口 */
	/* 输入输出端口 */
	char*			out;
	const char*			source;
	/* 状态变量 */
	/* 参数变量 */
} luaO_chunkid;

void luaO_chunkidFun(luaO_chunkid *pIp);
#endif // __LUAO_CHUNKID_H__