#include "equalkey.h"
void equalkeyFun(void *p) 
{
    equalkey *pIp = (equalkey*)p;
  {if ((rawtt(pIp->k1) != keytt(pIp->n2)) &&  /* not the same variants? */
       !(pIp->deadok && keyisdead(pIp->n2) && iscollectable(pIp->k1)))
   *(pIp->ret) =  0; } /* cannot be same key */
  {switch (keytt(pIp->n2)) {
    case LUA_VNIL: case LUA_VFALSE: case LUA_VTRUE:
      *(pIp->ret) =  1;
    case LUA_VNUMINT:
      *(pIp->ret) =  (ivalue(k1) == keyival(n2));
    case LUA_VNUMFLT:
      *(pIp->ret) =  luai_numeq(fltvalue(k1), fltvalueraw(keyval(n2)));
    case LUA_VLIGHTUSERDATA:
      *(pIp->ret) =  pvalue(k1) == pvalueraw(keyval(n2));
    case LUA_VLCF:
      *(pIp->ret) =  fvalue(k1) == fvalueraw(keyval(n2));
    case ctb(LUA_VLNGSTR):
      *(pIp->ret) =  luaS_eqlngstr(tsvalue(k1), keystrval(n2));
    default:
      *(pIp->ret) =  gcvalue(k1) == gcvalueraw(keyval(n2));
  }}
}