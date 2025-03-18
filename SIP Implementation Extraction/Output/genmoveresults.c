#include "genmoveresults.h"
void genmoveresultsFun(void *p) 
{
    genmoveresults *pIp = (genmoveresults*)p;

  StkId firstresult = pIp -> L->top.p - pIp -> nres;  /* index of first result */
  int i;
  if (pIp -> nres > pIp -> wanted)  /* extra results? */
    pIp -> nres = pIp -> wanted;  /* don't need them */
  for (i = 0; i < pIp -> nres; i++)  /* move all results to correct place */
    setobjs2s(pIp -> L, pIp -> res + i, firstresult + i);
  for (; i < pIp -> wanted; i++)  /* complete pIp -> wanted number of results */
    setnilvalue(s2v(pIp -> res + i));
  pIp -> L->top.p = pIp -> res + pIp -> wanted;  /* top points after the last result */
}