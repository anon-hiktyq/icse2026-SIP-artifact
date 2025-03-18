#include "filterpc.h"
void filterpcFun(void *p) 
{
    filterpc *pIp = (filterpc*)p;
  if (pIp -> pc < pIp -> jmptarget)  /* is code conditional (inside a jump)? */
    *(pIp -> ret) = -1; /* cannot know who sets that register */
  else return pIp -> pc;  /* current position sets that register */
}