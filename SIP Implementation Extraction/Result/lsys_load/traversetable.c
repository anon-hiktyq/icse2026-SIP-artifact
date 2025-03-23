#include "traversetable.h"
void traversetableFun(void *p) 
{
    traversetable *pIp = (traversetable*)p;
  const char *weakkey, *weakvalue;
  const TValue mode;{mode = gfasttm(pIp->g, pIp->h->metatable, TM_MODE);}
  TString *smode;
  {markobjectN(pIp->g, pIp->h->metatable);}
  {if (mode && ttisshrstring(mode) &&  /* is there a weak mode? */
      (cast_void(smode = tsvalue(mode)),
       cast_void(weakkey = strchr(getshrstr(smode), 'k')),
       cast_void(weakvalue = strchr(getshrstr(smode), 'v')),
       (weakkey || weakvalue))) {  /* is really weak? */
    if (!weakkey)  /* strong keys? */
      {IPCALL(traverseweakvalue,iptraverseweakvalue_0,.g = pIp->g,.h = pIp->h);}
    else if (!weakvalue)  /* strong values? */
      {int traverseephemeron_ret_0;IPCALL(traverseephemeron,iptraverseephemeron_0,.g = pIp->g,.h = pIp->h,.inv = 0,.ret = &traverseephemeron_ret_0);traverseephemeron_ret_0;}
    else  /* all weak */
      {linkgclist(pIp->h, pIp->g->allweak);}  /* nothing to traverse now */
  }
  else  /* not weak */
    {IPCALL(traversestrongtable,iptraversestrongtable_0,.g = pIp->g,.h = pIp->h);}}
  *(pIp->ret) =  1 + 2*sizenode(h) + h->asize;
}