
#include "filterpc.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->ret);
  assigns *(pIp->ret);
  ensures (pIp->pc < pIp->jmptarget) ==> *(pIp->ret) == -1;
  ensures (pIp->pc >= pIp->jmptarget) ==> *(pIp->ret) == pIp->pc;
*/
void filterpcFun(filterpc *pIp) 
{
  if (pIp->pc < pIp->jmptarget)  /* is code conditional (inside a jump)? */
    *(pIp->ret) = -1; /* cannot know who sets that register */
  else *(pIp->ret) = pIp->pc;  /* current position sets that register */
}
