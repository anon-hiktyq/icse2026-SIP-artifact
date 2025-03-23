#include "markold.h"
void markoldFun(void *p) 
{
    markold *pIp = (markold*)p;
  GCObject *p;
  for (p = (pIp->from); p != (pIp->to); p = p->next) {
    {if (getage(p) == G_OLD1) {
      {lua_assert(!iswhite(p));}
      {setage(p, G_OLD);}  /* now they are old */
      {if (isblack(p))
        {IPCALL(reallymarkobject,ipreallymarkobject_0,.g = pIp->g,.o = p);}}
    }}
  }
}