#if !defined(__LINKGCLIST__H__)
#define __LINKGCLIST__H__

#include "common.h"


#ifndef _LUA_ASSERT_
	#define lua_assert ((void)0)
#endif

#ifndef _ISGRAY_
	#define isgray (!testbits((x)->marked, WHITEBITS | bitmask(BLACKBIT)))
#endif

#ifndef _SET2GRAY_
	#define set2gray resetbits(x->marked, maskcolors)
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

#ifndef _GCOBJECT_
	struct GCObject {
	  CommonHeader;
	};
#endif


void linkgclist_Fun(void *p);

typedef struct __linkgclist_
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	/* Output Variables */
	/* In&Output Variables */
	GCObject*			o;
	GCObject**			pnext;
	GCObject**			list;
	/* Statement Variables*/
	/* Argument Variables */
} linkgclist_;

#endif // __LINKGCLIST__H__