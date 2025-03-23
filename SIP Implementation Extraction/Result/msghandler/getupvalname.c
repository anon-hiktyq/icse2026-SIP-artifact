#include "getupvalname.h"
void getupvalnameFun(void *p) 
{
    getupvalname *pIp = (getupvalname*)p;
  LClosure c;{c = ci_func(pIp->ci);}
  int i;
  for (i = 0; i < c->nupvalues; i++) {
    if (c->upvals[i]->v.p == (pIp->o)) {
      {const char * upvalname_ret_0;IPCALL(upvalname,ipupvalname_0,.p = c->p,.uv = i,.ret = upvalname_ret_0);*pIp->name = upvalname_ret_0;}
      pIp->ret =  "upvalue";
    }
  }
  pIp->ret =  NULL;
}