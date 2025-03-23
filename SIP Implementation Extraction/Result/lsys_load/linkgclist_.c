#include "linkgclist_.h"
void linkgclist_Fun(void *p) 
{
    linkgclist_ *pIp = (linkgclist_*)p;
  {lua_assert(!isgray(pIp->o));}  /* cannot be in a gray list */
  *(pIp->pnext) = *(pIp->list);
  *(pIp->list) = (pIp->o);
  {set2gray(pIp->o);}  /* now it is */
}