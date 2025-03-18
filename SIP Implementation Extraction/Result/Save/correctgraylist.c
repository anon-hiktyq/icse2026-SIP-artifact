#include "correctgraylist.h"
void correctgraylistFun(void *p) 
{
    correctgraylist *pIp = (correctgraylist*)p;
  GCObject *curr;
  while ((curr = pIp -> *p) != NULL) {
    GCObject **next;{GCObject ** getgclist_ret_0;IPCALL(getgclist,ipgetgclist_0,.o = curr,.ret = pIp->getgclist_ret_0);**next = getgclist_ret_0}
    if (iswhite(curr))
      goto remove;  /* remove all white objects */
    else if (getage(curr) == G_TOUCHED1) {  /* touched in this cycle? */
      lua_assert(isgray(curr));
      nw2black(curr);  /* make it black, for next barrier */
      setage(curr, G_TOUCHED2);
      goto remain;  /* keep it in the list and go to next element */
    }
    else if (curr->tt == LUA_VTHREAD) {
      lua_assert(isgray(curr));
      goto remain;  /* keep non-white threads on the list */
    }
    else {  /* everything else is removed */
      lua_assert(isold(curr));  /* young objects should be white here */
      if (getage(curr) == G_TOUCHED2)  /* advance from TOUCHED2... */
        setage(curr, G_OLD);  /* ... to OLD */
      nw2black(curr);  /* make object black (to be removed) */
      goto remove;
    }
    remove: pIp -> *p = *next; continue;
    remain: pIp -> p = next; continue;
  }
  pIp -> ret = p;
}