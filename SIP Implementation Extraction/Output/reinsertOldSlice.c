#include "reinsertOldSlice.h"
void reinsertOldSliceFun(void *p) 
{
    reinsertOldSlice *pIp = (reinsertOldSlice*)p;

  unsigned i;
  for (i = pIp -> newasize; i < pIp -> oldasize; i++) {  /* traverse vanishing slice */
    lu_byte tag = *getArrTag(pIp -> t, i);
    if (!tagisempty(tag)) {  /* a non-empty entry? */
      TValue key, aux;
      setivalue(&key, l_castU2S(i) + 1);  /* make the key */
      farr2val(pIp -> t, i, tag, &aux);  /* copy value into 'aux' */
      {int insertkey_ret_0;IPCALL(insertkey,ipinsertkey_0,.t = pIp->t,.key = &key,.value = &aux,.ret = &insertkey_ret_0);}  /* insert entry into the hash part */
    }
  }
}