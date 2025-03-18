
#include "DevControl.h"

/*@ 
  requires \valid(pIp); 
  assigns \nothing; 
*/
void DevControlFun(DevControl *pIp)
{
    /*@ 
      ensures \result == \old(\result); 
      assigns \nothing; 
    */
    ADDR_WRITE(0x881A, 0xEB92);

    /*@ 
      ensures \result == \old(\result); 
      assigns \nothing; 
    */
    ADDR_WRITE(0x8000, 0x01);

    /*@ 
      ensures \result == \old(\result); 
      assigns \nothing; 
    */
    ADDR_WRITE(0x8008, 0xFC);

    return;
}
