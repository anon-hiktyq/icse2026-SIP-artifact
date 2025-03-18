#if !defined(__LUAF_GETLOCALNAME_H__)
#define __LUAF_GETLOCALNAME_H__

#include "common.h"


#ifndef _GETSTR_
	#define getstr (strisshr(ts) ? rawgetshrstr(ts) : (ts)->contents)
#endif

#ifndef _LS_BYTE_
	typedef signed char ls_byte;
#endif

#ifndef _TSTRING_
	struct TString {
	  CommonHeader;
	  lu_byte extra;  /* reserved words for short strings; "has hash" for longs */
	  ls_byte shrlen;  /* length for short strings, negative for long strings */
	  unsigned int hash;
	  union {
	    size_t lnglen;  /* length for long strings */
	    struct TString *hnext;  /* linked list for hash table */
	  } u;
	  char *contents;  /* pointer to content in long strings */
	  lua_Alloc falloc;  /* deallocation function for external strings */
	  void *ud;  /* user data for external strings */
	};
#endif

#ifndef _LOCVAR_
	struct LocVar {
	  TString *varname;
	  int startpc;  /* first point where variable is active */
	  int endpc;    /* first point where variable is dead */
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


void luaF_getlocalnameFun(void *p);

typedef struct __luaF_getlocalname
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	const Proto*			f;
	int			local_number;
	int			pc;
	/* 输出端口 */
	const char *			ret;
	/* 输入输出端口 */
	/* 状态变量 */
	/* 参数变量 */
} luaF_getlocalname;

#endif // __LUAF_GETLOCALNAME_H__