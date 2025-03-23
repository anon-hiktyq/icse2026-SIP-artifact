#if !defined(__OBJSIZE_H__)
#define __OBJSIZE_H__

#include "common.h"
#include "luaH_size.h"
#include "luaF_protosize.h"
#include "luaE_threadsize.h"
#include "luaS_sizelngstr.h"

#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _cast_
#define _cast_
	#define cast ((t)(exp))
#endif

#ifndef _cast_uint_
#define _cast_uint_
	#define cast_uint cast(unsigned int, (i))
#endif

#ifndef _LUA_VTHREAD_
#define _LUA_VTHREAD_
	#define LUA_VTHREAD makevariant(LUA_TTHREAD, 0)
#endif

#ifndef _LUA_VSHRSTR_
#define _LUA_VSHRSTR_
	#define LUA_VSHRSTR makevariant(LUA_TSTRING, 0)
#endif

#ifndef _LUA_VLNGSTR_
#define _LUA_VLNGSTR_
	#define LUA_VLNGSTR makevariant(LUA_TSTRING, 1)
#endif

#ifndef _LUA_VUSERDATA_
#define _LUA_VUSERDATA_
	#define LUA_VUSERDATA makevariant(LUA_TUSERDATA, 0)
#endif

#ifndef _sizeudata_
#define _sizeudata_
	#define sizeudata (udatamemoffset(nuv) + (nb))
#endif

#ifndef _LUA_VPROTO_
#define _LUA_VPROTO_
	#define LUA_VPROTO makevariant(LUA_TPROTO, 0)
#endif

#ifndef _LUA_VUPVAL_
#define _LUA_VUPVAL_
	#define LUA_VUPVAL makevariant(LUA_TUPVAL, 0)
#endif

#ifndef _LUA_VLCL_
#define _LUA_VLCL_
	#define LUA_VLCL makevariant(LUA_TFUNCTION, 0)
#endif

#ifndef _LUA_VCCL_
#define _LUA_VCCL_
	#define LUA_VCCL makevariant(LUA_TFUNCTION, 2)
#endif

#ifndef _LUA_VTABLE_
#define _LUA_VTABLE_
	#define LUA_VTABLE makevariant(LUA_TTABLE, 0)
#endif

#ifndef _gco2ts_
#define _gco2ts_
	#define gco2ts check_exp(novariant((o)->tt) == LUA_TSTRING, &((cast_u(o))->ts))
#endif

#ifndef _gco2u_
#define _gco2u_
	#define gco2u check_exp((o)->tt == LUA_VUSERDATA, &((cast_u(o))->u))
#endif

#ifndef _gco2lcl_
#define _gco2lcl_
	#define gco2lcl check_exp((o)->tt == LUA_VLCL, &((cast_u(o))->cl.l))
#endif

#ifndef _gco2ccl_
#define _gco2ccl_
	#define gco2ccl check_exp((o)->tt == LUA_VCCL, &((cast_u(o))->cl.c))
#endif

#ifndef _gco2t_
#define _gco2t_
	#define gco2t check_exp((o)->tt == LUA_VTABLE, &((cast_u(o))->h))
#endif

#ifndef _gco2p_
#define _gco2p_
	#define gco2p check_exp((o)->tt == LUA_VPROTO, &((cast_u(o))->p))
#endif

#ifndef _gco2th_
#define _gco2th_
	#define gco2th check_exp((o)->tt == LUA_VTHREAD, &((cast_u(o))->th))
#endif

#ifndef _sizeCclosure_
#define _sizeCclosure_
	#define sizeCclosure (offsetof(CClosure, upvalue) + sizeof(TValue) * cast_uint(n))
#endif

#ifndef _sizeLclosure_
#define _sizeLclosure_
	#define sizeLclosure (offsetof(LClosure, upvals) + sizeof(UpVal *) * cast_uint(n))
#endif

#ifndef _sizestrshr_
#define _sizestrshr_
	#define sizestrshr (offsetof(TString, contents) + ((l) + 1) * sizeof(char))
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State;
#endif

#ifndef _lu_mem_
#define _lu_mem_
	typedef size_t lu_mem;
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif

#ifndef _ls_byte_
#define _ls_byte_
	typedef signed char ls_byte;
#endif

#ifndef _GCObject_
#define _GCObject_
	struct GCObject {
	  CommonHeader;
	};
#endif

#ifndef _TString_
#define _TString_
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

#ifndef _Udata_
#define _Udata_
	struct Udata {
	  CommonHeader;
	  unsigned short nuvalue;  /* number of user values */
	  size_t len;  /* number of bytes */
	  struct Table *metatable;
	  GCObject *gclist;
	  UValue uv[1];  /* user values */
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

#ifndef _CClosure_
#define _CClosure_
	struct CClosure {
	  ClosureHeader;
	  lua_CFunction f;
	  TValue upvalue[1];  /* list of upvalues */
	};
#endif

#ifndef _LClosure_
#define _LClosure_
	struct LClosure {
	  ClosureHeader;
	  struct Proto *p;
	  UpVal *upvals[1];  /* list of upvalues */
	};
#endif

#ifndef _Closure_
#define _Closure_
	union Closure {
	  CClosure c;
	  LClosure l;
	};
#endif

#ifndef _Table_
#define _Table_
	struct Table {
	  CommonHeader;
	  lu_byte flags;  /* 1<<p means tagmethod(p) is not present */
	  lu_byte lsizenode;  /* log2 of number of slots of 'node' array */
	  unsigned int asize;  /* number of slots in 'array' array */
	  Value *array;  /* array part */
	  Node *node;
	  struct Table *metatable;
	  GCObject *gclist;
	};
#endif

#ifndef _lua_State_
#define _lua_State_
	struct lua_State {
	  CommonHeader;
	  lu_byte allowhook;
	  TStatus status;
	  StkIdRel top;  /* first free slot in the stack */
	  struct global_State *l_G;
	  CallInfo *ci;  /* call info for current function */
	  StkIdRel stack_last;  /* end of stack (last element + 1) */
	  StkIdRel stack;  /* stack base */
	  UpVal *openupval;  /* list of open upvalues in this stack */
	  StkIdRel tbclist;  /* list of to-be-closed variables */
	  GCObject *gclist;
	  struct lua_State *twups;  /* list of threads with open upvalues */
	  struct lua_longjmp *errorJmp;  /* current error recover point */
	  CallInfo base_ci;  /* CallInfo for first level (C host) */
	  volatile lua_Hook hook;
	  ptrdiff_t errfunc;  /* current error handling function (stack index) */
	  l_uint32 nCcalls;  /* number of nested non-yieldable or C calls */
	  int oldpc;  /* last pc traced */
	  int nci;  /* number of items in 'ci' list */
	  int basehookcount;
	  int hookcount;
	  volatile l_signalT hookmask;
	  struct {  /* info about transferred values (for call/return hooks) */
	    int ftransfer;  /* offset of first value transferred */
	    int ntransfer;  /* number of values transferred */
	  } transferinfo;
	};
#endif


void objsizeFun(void *p);

typedef struct __objsize
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	GCObject*			o;
	/* Output Variables */
	l_mem*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} objsize;

#endif // __OBJSIZE_H__