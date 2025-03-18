#if !defined(__LUAS_NEWUDATA_H__)
#define __LUAS_NEWUDATA_H__

#include "common.h"
#include luaM_toobig.h
#include luaC_newobj.h

#ifndef _L_UNLIKELY_
	#define l_unlikely luai_unlikely(x)
#endif

#ifndef _MAX_SIZE_
	#define MAX_SIZE (sizeof(size_t) < sizeof(lua_Integer) ? MAX_SIZET \
				  : cast_sizet(LUA_MAXINTEGER))
#endif

#ifndef _SETNILVALUE_
	#define setnilvalue settt_(obj, LUA_VNIL)
#endif

#ifndef _LUA_VUSERDATA_
	#define LUA_VUSERDATA makevariant(LUA_TUSERDATA, 0)
#endif

#ifndef _UDATAMEMOFFSET_
	#define udatamemoffset ((nuv) == 0 ? offsetof(Udata0, bindata)  \
			   : offsetof(Udata, uv) + (sizeof(UValue) * (nuv)))
#endif

#ifndef _SIZEUDATA_
	#define sizeudata (udatamemoffset(nuv) + (nb))
#endif

#ifndef _GCO2U_
	#define gco2u check_exp((o)->tt == LUA_VUSERDATA, &((cast_u(o))->u))
#endif

struct lua_State;
#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

struct TValue {
  TValuefields;
};
struct GCObject {
  CommonHeader;
};
#ifndef _UVALUE_
	union UValue {
	  TValue uv;
	  LUAI_MAXALIGN;  /* ensures maximum alignment for udata bytes */
	};
#endif

#ifndef _UDATA_
	struct Udata {
	  CommonHeader;
	  unsigned short nuvalue;  /* number of user values */
	  size_t len;  /* number of bytes */
	  struct Table *metatable;
	  GCObject *gclist;
	  UValue uv[1];  /* user values */
	};
#endif

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

void luaS_newudataFun(void *p);

typedef struct __luaS_newudata
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	size_t			s;
	unsigned short			nuvalue;
	/* Output Variables */
	Udata*			u;
	Udata *			ret;
	/* In&Output Variables */
	lua_State*			L;
	/* Statement Variables*/
	/* Argument Variables */
} luaS_newudata;

#endif // __LUAS_NEWUDATA_H__