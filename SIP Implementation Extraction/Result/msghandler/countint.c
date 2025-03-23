#include "countint.h"
void countintFun(void *p) 
{
    countint *pIp = (countint*)p;
  unsigned int k;{k = arrayindex(pIp->key);}
  if (k != 0) {  /* is 'key' an array index? */
    {lu_byte luaO_ceillog2_ret_0;IPCALL(luaO_ceillog2,ipluaO_ceillog2_0,.ret = &luaO_ceillog2_ret_0);pIp->ct->nums[luaO_ceillog2_ret_0]++;}  /* count as such */
    (pIp->ct)->na++;
  }
}