#if !defined(__GETBASELINE_H__)
#define __GETBASELINE_H__

#include "common.h"


#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _MAXIWTHABS_
	#define MAXIWTHABS 128
#endif

#ifndef _ABSLINEINFO_
	struct AbsLineInfo {
	  int pc;
	  int line;
	};
#endif

#ifndef _PROTO_
	struct Proto {
	  CommonHeader;
	  lu_byte numparams;  /* number of fixed (named) parameters */
	  lu_byte flag;
	  lu_byte maxstacksize;  /* number of registers needed by this function */
	  int sizeupvalues;  /* size of 'upvalues' */
	  int sizek;  /* size of 'k' */
	  int sizecode;
	  int sizelineinfo;
	  int sizep;  /* size of 'p' */
	  int sizelocvars;
	  int sizeabslineinfo;  /* size of 'abslineinfo' */
	  int linedefined;  /* debug information  */
	  int lastlinedefined;  /* debug information  */
	  TValue *k;  /* constants used by the function */
	  Instruction *code;  /* opcodes */
	  struct Proto **p;  /* functions defined inside the function */
	  Upvaldesc *upvalues;  /* upvalue information */
	  ls_byte *lineinfo;  /* information about source lines (debug information) */
	  AbsLineInfo *abslineinfo;  /* idem */
	  LocVar *locvars;  /* information about local variables (debug information) */
	  TString  *source;  /* used for debug information */
	  GCObject *gclist;
	};
#endif


void getbaselineFun(void *p);

typedef struct __getbaseline
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	const Proto*			f;
	int			pc;
	/* 输出端口 */
	int*			ret;
	/* 输入输出端口 */
	int*			basepc;
	/* 状态变量 */
	/* 参数变量 */
} getbaseline;

#endif // __GETBASELINE_H__