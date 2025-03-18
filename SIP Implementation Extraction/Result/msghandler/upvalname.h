#if !defined(__UPVALNAME_H__)
#define __UPVALNAME_H__

#include "common.h"


#ifndef _CHECK_EXP_
	#define check_exp (lua_assert(c), (e))
#endif

#ifndef _GETSTR_
	#define getstr (strisshr(ts) ? rawgetshrstr(ts) : (ts)->contents)
#endif

typedef signed char ls_byte;
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
#ifndef _UPVALDESC_
	struct Upvaldesc {
	  TString *name;  /* upvalue name (for debug information) */
	  lu_byte instack;  /* whether it is in stack (register) */
	  lu_byte idx;  /* index of upvalue (in stack or in outer function's list) */
	  lu_byte kind;  /* kind of corresponding variable */
	};
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

void upvalnameFun(void *p);

typedef struct __upvalname
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const Proto*			p;
	int			uv;
	/* Output Variables */
	const char *			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} upvalname;

#endif // __UPVALNAME_H__