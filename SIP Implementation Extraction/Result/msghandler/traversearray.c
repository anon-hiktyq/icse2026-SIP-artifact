#include "traversearray.h"
void traversearrayFun(void *p) 
{
    traversearray *pIp = (traversearray*)p;
  unsigned asize = (pIp->h)->asize;
  int marked = 0;  /* true if some object is marked in this traversal */
  unsigned i;
  for (i = 0; i < asize; i++) {
    GCObject o;{o = gcvalarr(pIp->h, i);}
    {if (o != NULL && iswhite(o)) {
      marked = 1;
      {IPCALL(reallymarkobject,ipreallymarkobject_0,.g = pIp->g,.o = o);}
    }}
  }
  *(pIp->ret) =  marked;
}