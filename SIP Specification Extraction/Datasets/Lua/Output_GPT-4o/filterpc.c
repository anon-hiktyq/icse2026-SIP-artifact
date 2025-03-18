
#include "filterpc.h"

/*@
  requires \valid(pIp);  // Ensure the pointer pIp is valid
  requires \valid(pIp->ret);  // Ensure the pointer pIp->ret is valid
  assigns *(pIp->ret);  // The function modifies the value pointed to by pIp->ret
  ensures (pIp->pc < pIp->jmptarget) ==> *(pIp->ret) == -1;  // Postcondition: if pIp->pc is less than pIp->jmptarget, then the value pointed to by pIp->ret is set to -1
*/
void filterpcFun(filterpc *pIp) 
{
  if (pIp->pc < pIp->jmptarget)  /* is code conditional (inside a jump)? */
    *(pIp->ret) = -1; /* cannot know who sets that register */
}
