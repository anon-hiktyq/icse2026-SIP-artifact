#include "getcurrentline.h"
void getcurrentlineFun(void *p) 
{
    getcurrentline *pIp = (getcurrentline*)p;
  *(pIp -> ret) = luaG_getfuncline(ci_func(ci)->p, currentpc(ci));
}