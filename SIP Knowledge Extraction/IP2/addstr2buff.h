#if !defined(__ADDSTR2BUFF_H__)
#define __ADDSTR2BUFF_H__

#include "common.h"
#include luaM_realloc_.h

#define MAX_SIZE (sizeof(size_t) < sizeof(lua_Integer) ? MAX_SIZET \
			  : cast_sizet(LUA_MAXINTEGER))
#ifndef _LUAM_REALLOCVECTOR_
	#define luaM_reallocvector (cast(t *, luaM_realloc_(L, v, cast_sizet(oldn) * sizeof(t), \
	                                  cast_sizet(n) * sizeof(t))))
#endif

struct lua_State;
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
#ifndef _BUFFFS_
	struct BuffFS {
	  lua_State *L;
	  char *b;
	  size_t buffsize;
	  size_t blen;  /* length of string in 'buff' */
	  int err;
	  char space[BUFVFS];  /* initial buffer */
	};
#endif


void addstr2buffFun(void *p);

typedef struct __addstr2buff
{
/* 接口函数 */
	Fun			fun;
/* 输入端口 */
	size_t			slen;
	/* 输出端口 */
	/* 输入输出端口 */
	BuffFS*			buff;
	const char*			str;
	/* 状态变量 */
	/* 参数变量 */
} addstr2buff;

#endif // __ADDSTR2BUFF_H__