#include "luaD_seterrorobj.h"
void luaD_seterrorobjFun(void *p) 
{
    luaD_seterrorobj *pIp = (luaD_seterrorobj*)p;
  switch ((pIp->errcode)) {
    case LUA_ERRMEM: {  /* memory error? */
      {setsvalue2s(pIp->L, pIp->oldtop, G(pIp->L)->memerrmsg);} /* reuse preregistered msg. */
      break;
    }
    case LUA_ERRERR: {
      {setsvalue2s(pIp->L, pIp->oldtop, luaS_newliteral(pIp->L, "error in error handling"));}
      break;
    }
    default: {
      {lua_assert(errorstatus(pIp->errcode));}  /* must be a real error */
      {if (!ttisnil(s2v(pIp->L->top.p - 1))) {  /* error object is not nil? */
        {setobjs2s(pIp->L, pIp->oldtop, pIp->L->top.p - 1);}  /* move it to 'oldtop' */
      }
      else  /* change it to a proper message */
        {setsvalue2s(pIp->L, pIp->oldtop, luaS_newliteral(pIp->L, "<error object is nil>"));}}
      break;
    }
  }
  (pIp->L)->top.p = (pIp->oldtop) + 1;  /* top goes back to old top plus error object */
}