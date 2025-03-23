#include "numusearray.h"
void numusearrayFun(void *p) 
{
    numusearray *pIp = (numusearray*)p;
  int lg;
  unsigned int ttlg;  /* 2^lg */
  unsigned int ause = 0;  /* summation of 'nums' */
  unsigned int i = 1;  /* index to traverse all array keys */
  unsigned int asize = (pIp->t)->asize;
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
      {int arraykeyisempty_ret_0;IPCALL(arraykeyisempty,iparraykeyisempty_0,.t = pIp->t,.key = i,.ret = &arraykeyisempty_ret_0);if (!arraykeyisempty_ret_0)
        lc++;}
    }
    (pIp->ct)->nums[lg] += lc;
    ause += lc;
  }
  (pIp->ct)->total += ause;
  (pIp->ct)->na += ause;
}