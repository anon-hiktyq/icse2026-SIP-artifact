#if !defined(__CHANGEDLINE_H__)
#define __CHANGEDLINE_H__

#include "common.h"
#include "luaG_getfuncline.h"

#ifndef _ABSLINEINFO_
	#define ABSLINEINFO (-0x80)
#endif

#ifndef _MAXIWTHABS_
	#define MAXIWTHABS 128
#endif

#ifndef _LS_BYTE_
	typedef signed char ls_byte;
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


void changedlineFun(void *p);

typedef struct __changedline
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const Proto*			p;
	int			oldpc;
	int			newpc;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} changedline;

#endif // __CHANGEDLINE_H__