
#include "main.h"

/*@
  // Precondition: pIp and pIp->ret must be valid pointers
  requires \valid(pIp);
  requires \valid(pIp->ret);
  
  // The function assigns to the memory pointed by pIp->ret
  assigns *(pIp->ret);
  
  // Postcondition: The value pointed by pIp->ret is set to 0
  ensures *(pIp->ret) == 0;
*/
void mainFun(main *pIp) 
{
    int value = 5;

    // Call to funa with the result of funb(value) as a parameter
    /*@
      // Assuming IPCALL does not modify any global state
      assigns \nothing;
    */
    {IPCALL(funa, ipfuna, .y = funb(value));}

    // Set the value pointed by pIp->ret to 0
    *(pIp -> ret) = 0;
}
