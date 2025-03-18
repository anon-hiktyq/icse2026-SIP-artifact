#if !defined(__NEXTLINE_H__)
#define __NEXTLINE_H__

#include "common.h"
#include luaG_getfuncline.h

#ifndef _ABSLINEINFO_
	#define ABSLINEINFO (-0x80)
#endif

typedef signed char ls_byte;
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

void nextlineFun(void *p);

typedef struct __nextline
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const Proto*			p;
	int			currentline;
	int			pc;
	/* Output Variables */
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} nextline;

#endif // __NEXTLINE_H__