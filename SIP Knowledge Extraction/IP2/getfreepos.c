#include "getfreepos.h"
void getfreeposFun(void *p) 
{
    getfreepos *pIp = (getfreepos*)p;
  if (haslastfree(pIp -> t)) {  /* does it have 'lastfree' information? */
    /* look for a spot before 'lastfree', updating 'lastfree' */
    while (getlastfree(pIp -> t) > pIp -> t->node) {
      Node *free = --getlastfree(pIp -> t);
      if (keyisnil(free))
        pIp -> ret = free;
    }
  }
  else {  /* no 'lastfree' information */
    unsigned i = sizenode(pIp -> t);
    while (i--) {  /* do a linear search */
      Node *free = gnode(pIp -> t, i);
      if (keyisnil(free))
        pIp -> ret = free;
    }
  }
  pIp -> ret = NULL; /* could not find a free place */
}