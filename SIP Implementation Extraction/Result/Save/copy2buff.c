#include "copy2buff.h"
void copy2buffFun(void *p) 
{
    copy2buff *pIp = (copy2buff*)p;
  size_t tl = 0;  /* size already copied */
  do {
    TString st;{st = tsvalue(s2v(pIp->top - pIp->n));}
    size_t l;  /* length of string being copied */
    const char s;{s = getlstr(st, l);}
    memcpy((pIp->buff) + tl, s, l * sizeof(char));
    tl += l;
  } while (--(pIp->n) > 0);
}