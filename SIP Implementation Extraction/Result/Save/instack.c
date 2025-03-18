#include "instack.h"
void instackFun(void *p) 
{
    instack *pIp = (instack*)p;
  int pos;
  StkId base = pIp -> ci->func.p + 1;
  for (pos = 0; base + pos < pIp -> ci->top.p; pos++) {
    if (pIp -> o == s2v(base + pos))
      *(pIp -> ret) = pos;
  }
  *(pIp -> ret) = -1; /* not found */
}