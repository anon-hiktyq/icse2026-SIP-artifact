#if !defined(__LUAF_PROTOSIZE_H__)
#define __LUAF_PROTOSIZE_H__

#include "common.h"


#ifndef _CAST_
	#define cast ((t)(exp))
#endif

#ifndef _CAST_UINT_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _PF_FIXED_
	#define PF_FIXED 2
#endif

#ifndef _LU_MEM_
	typedef size_t lu_mem;
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

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

void luaF_protosizeFun(void *p);

typedef struct __luaF_protosize
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	Proto*			p;
	/* Output Variables */
	lu_mem			sz;
	lu_mem*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} luaF_protosize;

#endif // __LUAF_PROTOSIZE_H__