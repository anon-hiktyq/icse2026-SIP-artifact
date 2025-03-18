#include "findvararg.h"
void findvarargFun(void *p) 
{
    findvararg *pIp = (findvararg*)p;
  if (clLvalue(s2v(pIp -> ci->func.p))->p->flag & PF_ISVARARG) {
    int nextra = pIp -> ci->u.l.nextraargs;
    if (pIp -> n >= -nextra) {  /* 'pIp -> n' is negative */
      pIp -> *pos = pIp -> ci->func.p - nextra - (pIp -> n + 1);
      pIp -> ret = "(vararg)"; /* generic name for any vararg */
    }
  }
  pIp -> ret = NULL; /* no such vararg */
}