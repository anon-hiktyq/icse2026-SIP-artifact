#include "hashint.h"
void hashintFun(void *p) 
{
    hashint *pIp = (hashint*)p;
  lua_Unsigned ui;{ui = l_castS2U(pIp->i);}
  {if (ui <= cast_uint(INT_MAX))
    pIp->ret =  gnode(t, cast_int(ui) % cast_int((sizenode(t)-1) | 1));
  else
    pIp->ret =  hashmod(t, ui);}
}