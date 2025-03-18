#if !defined(__ISENV_H__)
#define __ISENV_H__

#include "common.h"
#include "upvalname.h"
#include "basicgetobjname.h"

#ifndef _LUA_ENV_
	#define LUA_ENV "_ENV"
#endif

#ifndef _GETARG_B_
	#define GETARG_B check_exp(checkopm(i, iABC), getarg(i, POS_B, SIZE_B))
#endif

typedef l_uint32 Instruction;
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


void isEnvFun(void *p);

typedef struct __isEnv
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	Instruction			i;
	int			isup;
	/* Output Variables */
	const char *			ret;
	/* In&Output Variables */
	const Proto*			p;
	/* Statement Variables*/
	/* Argument Variables */
} isEnv;

#endif // __ISENV_H__