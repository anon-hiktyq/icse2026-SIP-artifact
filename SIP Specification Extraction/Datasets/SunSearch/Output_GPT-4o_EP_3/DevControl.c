
#include "DevControl.h"

/*@ 
  requires \valid(pIp);
  assigns \nothing;
*/
void DevControlFun(DevControl *pIp)
{
    /*@ 
      assigns \nothing;
    */
    ADDR_WRITE(0x881A, 0xEB92);

    /*@ 
      assigns \nothing;
    */
    ADDR_WRITE(0x8000, 0x01);

    /*@ 
      assigns \nothing;
    */
    ADDR_WRITE(0x8008, 0xFC);

    return;
}
