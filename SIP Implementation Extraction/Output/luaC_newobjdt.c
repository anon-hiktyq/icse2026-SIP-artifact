#include "luaC_newobjdt.h"
void luaC_newobjdtFun(void *p) 
{
    luaC_newobjdt *pIp = (luaC_newobjdt*)p;
  global_State *g = G(pIp -> L);
  char *p = cast_charp(luaM_newobject(pIp -> L, novariant(pIp -> tt), pIp -> sz));
  GCObject *o = cast(GCObject *, p + pIp -> offset);
  o->marked = luaC_white(g);
  o->pIp -> tt = pIp -> tt;
  o->next = g->allgc;
  g->allgc = o;
  pIp -> ret = o;
}