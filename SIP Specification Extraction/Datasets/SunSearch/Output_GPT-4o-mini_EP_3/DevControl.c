
#include "DevControl.h"

/*@ 
  requires \valid(pIp); 
  assigns \nothing; 
*/
void DevControlFun(DevControl *pIp)
{
    /*@ 
      requires \valid(pIp); 
      assigns \nothing; 
    */
    ADDR_WRITE(0x881A, 0xEB92);

    /*@ 
      requires \valid(pIp); 
      assigns \nothing; 
    */
    ADDR_WRITE(0x8000, 0x01);

    /*@ 
      requires \valid(pIp); 
      assigns \nothing; 
    */
    ADDR_WRITE(0x8008, 0xFC);

    return;
}
