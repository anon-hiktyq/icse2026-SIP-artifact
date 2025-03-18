#include "newbuffsize.h"
void newbuffsizeFun(void *p) 
{
    newbuffsize *pIp = (newbuffsize*)p;
  size_t newsize = (pIp -> B->size / 2) * 3;  /* buffer size * 1.5 */
  if (l_unlikely(pIp -> sz > MAX_SIZE - pIp -> B->n - 1))
    *(pIp -> ret) = cast_sizet(luaL_error(B->L, "resulting string too large"));
  if (newsize < pIp -> B->n + pIp -> sz + 1 || newsize > MAX_SIZE) {
    /* newsize was not big enough or too big */
    newsize = pIp -> B->n + pIp -> sz + 1;
  }
  *(pIp -> ret) = newsize;
}