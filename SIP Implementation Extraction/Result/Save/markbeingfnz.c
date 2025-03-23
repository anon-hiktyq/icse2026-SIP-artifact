#include "markbeingfnz.h"
void markbeingfnzFun(void *p) 
{
    markbeingfnz *pIp = (markbeingfnz*)p;
  GCObject *o;
  for (o = (pIp->g)->tobefnz; o != NULL; o = o->next)
    {markobject(pIp->g, o);}
}