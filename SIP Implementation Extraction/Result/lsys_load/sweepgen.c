#include "sweepgen.h"
void sweepgenFun(void *p) 
{
    sweepgen *pIp = (sweepgen*)p;


  static const lu_byte nextage[] = {
    G_SURVIVAL,  /* from G_NEW */
    G_OLD1,      /* from G_SURVIVAL */
    G_OLD1,      /* from G_OLD0 */
    G_OLD,       /* from G_OLD1 */
    G_OLD,       /* from G_OLD (do not change) */
    G_TOUCHED1,  /* from G_TOUCHED1 (do not change) */
    G_TOUCHED2   /* from G_TOUCHED2 (do not change) */
  };
  l_mem addedold = 0;
  int white = luaC_white(pIp -> g);
  GCObject *curr;
  while ((curr = pIp -> *p) != pIp -> limit) {
    if (iswhite(curr)) {  /* is 'curr' dead? */
      lua_assert(!isold(curr) && isdead(pIp -> g, curr));
      pIp -> *p = curr->next;  /* remove 'curr' from list */
      {IPCALL(freeobj,ipfreeobj_0,.L = pIp->L,.o = curr);}  /* erase 'curr' */
    }
    else {  /* correct mark and age */
      int age = getage(curr);
      if (age == G_NEW) {  /* new objects go back to white */
        int marked = curr->marked & ~maskgcbits;  /* erase GC bits */
        curr->marked = cast_byte(marked | G_SURVIVAL | white);
      }
      else {  /* all other objects will be old, and so keep their color */
        lua_assert(age != G_OLD1);  /* advanced in 'markold' */
        setage(curr, nextage[age]);
        if (getage(curr) == G_OLD1) {
          addedold += objsize(curr);  /* bytes becoming old */
          if (pIp -> *pfirstold1 == NULL)
            pIp -> *pfirstold1 = curr;  /* first OLD1 object in the list */
        }
      }
      pIp -> p = &curr->next;  /* go to next element */
    }
  }
  pIp -> *paddedold += addedold;
  pIp -> ret = p;
}