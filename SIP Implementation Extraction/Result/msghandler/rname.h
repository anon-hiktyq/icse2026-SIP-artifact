#if !defined(__RNAME_H__)
#define __RNAME_H__

#include "common.h"
#include basicgetobjname.h

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

void rnameFun(void *p);

typedef struct __rname
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	int			c;
	/* Output Variables */
	/* In&Output Variables */
	const Proto*			p;
	const char**			name;
	/* Statement Variables*/
	/* Argument Variables */
} rname;

#endif // __RNAME_H__