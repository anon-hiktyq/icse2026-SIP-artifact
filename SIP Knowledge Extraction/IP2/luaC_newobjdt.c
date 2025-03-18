#include "luaC_newobjdt.h"
void luaC_newobjdtFun(void *p) 
{
    luaC_newobjdt *pIp = (luaC_newobjdt*)p;
  global_State *g = G(pIp -> L);
  char *p = cast_charp(luaM_newobject(pIp -> L, novariant(pIp -> tt), pIp -> sz));
  GCObject pIp -> *o = cast(GCObject *, p + pIp -> offset);
  pIp -> o->marked = luaC_white(g);
  pIp -> o->pIp -> tt = pIp -> tt;
  pIp -> o->next = g->allgc;
  g->allgc = pIp -> o;
  pIp -> ret = o;
}