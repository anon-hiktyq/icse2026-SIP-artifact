#if !defined(__LINKGCLIST__H__)
#define __LINKGCLIST__H__

#include "common.h"


#ifndef _lua_assert_
#define _lua_assert_
	#define lua_assert ((void)0)
#endif

#ifndef _isgray_
#define _isgray_
	#define isgray (!testbits((x)->marked, WHITEBITS | bitmask(BLACKBIT)))
#endif

#ifndef _set2gray_
#define _set2gray_
	#define set2gray resetbits(x->marked, maskcolors)
#endif

#ifndef _lu_byte_
#define _lu_byte_
	typedef unsigned char lu_byte;
#endif

#ifndef _GCObject_
#define _GCObject_
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