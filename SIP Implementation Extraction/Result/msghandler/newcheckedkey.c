#include "newcheckedkey.h"
void newcheckedkeyFun(void *p) 
{
    newcheckedkey *pIp = (newcheckedkey*)p;
  unsigned i;{unsigned int keyinarray_ret_0; IPCALL(keyinarray,ipkeyinarray_0,.t = pIp->t,.key = pIp->key,.ret = &keyinarray_ret_0);i = keyinarray_ret_0;}
  if (i > 0)  /* is key in the array part? */
    {obj2arr(pIp->t, i - 1, pIp->value);}  /* set value in the array */
  else {
    int done;{int insertkey_ret_0; IPCALL(insertkey,ipinsertkey_0,.t = pIp->t,.key = pIp->key,.value = pIp->value,.ret = &insertkey_ret_0);done = insertkey_ret_0;}  /* insert key in the hash part */
    {lua_assert(done);}  /* it cannot fail */
    {cast(void, done);}  /* to avoid warnings */
  }
}