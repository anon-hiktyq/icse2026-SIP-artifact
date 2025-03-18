
#include "funa.h"

/*@
  requires \valid(pIp);
  assigns \nothing;
*/
void funaFun(funa *pIp) 
{
    /*@ assert \valid(pIp); */
    printf("The result is: %d\n", pIp -> y);
}
