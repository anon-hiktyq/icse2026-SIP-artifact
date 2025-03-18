#include "numusearray.h"

void numusearrayFun(numusearray *pIp) 
{
  int lg;
  unsigned int ttlg;  /* 2^lg */
  unsigned int ause = 0;  /* summation of 'nums' */
  unsigned int i = 1;  /* index to traverse all array keys */
  unsigned int asize = pIp -> t->asize;
  /* traverse each slice */
  for (lg = 0, ttlg = 1; lg <= MAXABITS; lg++, ttlg *= 2) {
    unsigned int lc = 0;  /* counter */
    unsigned int lim = ttlg;
    if (lim > asize) {
      lim = asize;  /* adjust upper limit */
      if (i > lim)
        break;  /* no more elements to count */
    }
    /* count elements in range (2^(lg - 1), 2^lg] */
    for (; i <= lim; i++) {
      if (pIp -> t + i ==NULL)
        lc++;
    }
    pIp -> ct->nums[lg] += lc;
    ause += lc;
  }
  pIp -> ct->total += ause;
  pIp -> ct->na += ause;
}