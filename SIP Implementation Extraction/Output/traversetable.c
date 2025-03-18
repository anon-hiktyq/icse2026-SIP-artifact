#include "traversetable.h"
void traversetableFun(void *p) 
{
    traversetable *pIp = (traversetable*)p;
  const char *weakkey, *weakvalue;
  const TValue *mode = gfasttm(pIp -> g, pIp -> h->metatable, TM_MODE);
  TString *smode;
  {IPCALL(reallymarkobject,ipreallymarkobject_0,.g = pIp->g,.o = h->metatable);}
  if (mode && ttisshrstring(mode) &&  /* is there a weak mode? */
      (cast_void(smode = tsvalue(mode)),
       cast_void(weakkey = strchr(getshrstr(smode), 'k')),
       cast_void(weakvalue = strchr(getshrstr(smode), 'v')),
       (weakkey || weakvalue))) {  /* is really weak? */
    if (!weakkey)  /* strong keys? */
      traverseweakvalue(pIp -> g, pIp -> h);
    else if (!weakvalue)  /* strong values? */
      traverseephemeron(pIp -> g, pIp -> h, 0);
    else  /* all weak */
      linkgclist(pIp -> h, pIp -> g->allweak);  /* nothing to traverse now */
  }
  else  /* not weak */
    traversestrongtable(pIp -> g, pIp -> h);
  *(pIp -> ret) = 1 + 2*sizenode(h) + h->asize;
}