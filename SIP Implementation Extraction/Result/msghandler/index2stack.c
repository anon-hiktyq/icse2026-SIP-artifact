#include "index2stack.h"
void index2stackFun(void *p) 
{
    index2stack *pIp = (index2stack*)p;
  CallInfo *ci = pIp -> L->ci;
  if (pIp -> idx > 0) {
    StkId o = ci->func.p + pIp -> idx;
    api_check(pIp -> L, o < pIp -> L->top.p, "invalid index");
    *(pIp -> ret) = o;
  }
  else {    /* non-positive index */
    api_check(pIp -> L, pIp -> idx != 0 && -pIp -> idx <= pIp -> L->top.p - (ci->func.p + 1),
                 "invalid index");
    api_check(pIp -> L, !ispseudo(pIp -> idx), "invalid index");
    *(pIp -> ret) = L->top.p + idx;
  }
}