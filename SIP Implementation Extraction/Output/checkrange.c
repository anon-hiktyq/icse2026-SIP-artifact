#include "checkrange.h"
void checkrangeFun(void *p) 
{
    checkrange *pIp = (checkrange*)p;
  *(pIp -> ret) = (l_castS2U(k) - 1u < limit) ? cast_uint(k) : 0;
}