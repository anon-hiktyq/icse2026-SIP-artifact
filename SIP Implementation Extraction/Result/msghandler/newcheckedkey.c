#include "newcheckedkey.h"
void newcheckedkeyFun(void *p) 
{
    newcheckedkey *pIp = (newcheckedkey*)p;
  unsigned i;{unsigned int keyinarray_ret_1;IPCALL(keyinarray,ipkeyinarray_0,.t = pIp->t,.key = pIp->key,.ret = &keyinarray_ret_1);i = keyinarray_ret_1}
  if (i > 0)  /* is pIp -> key in the array part? */
    obj2arr(pIp -> t, i - 1, pIp -> value);  /* set pIp -> value in the array */
  else {
    int done;{int insertkey_ret_0;IPCALL(insertkey,ipinsertkey_0,.t = pIp->t,.key = pIp->key,.value = pIp->value,.ret = &insertkey_ret_0);done = insertkey_ret_0}  /* insert pIp -> key in the hash part */
    lua_assert(done);  /* it cannot fail */
    cast(void, done);  /* to avoid warnings */
  }
}