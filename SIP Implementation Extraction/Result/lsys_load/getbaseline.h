#if !defined(__GETBASELINE_H__)
#define __GETBASELINE_H__

#include "common.h"


#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _MAXIWTHABS_
#define _MAXIWTHABS_
	#define MAXIWTHABS 128
#endif

#ifndef _AbsLineInfo_
#define _AbsLineInfo_
	struct AbsLineInfo {
	  int pc;
	  int line;
	};
#endif

#ifndef _Proto_
#define _Proto_
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
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const Proto*			f;
	int			pc;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	int*			basepc;
	/* Statement Variables*/
	/* Argument Variables */
} getbaseline;

#endif // __GETBASELINE_H__