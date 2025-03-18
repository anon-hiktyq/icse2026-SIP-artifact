
#include "DevControl.h"

/*@ requires pIp != \null; 
    assigns \nothing; 
    ensures \exists integer addr, value; 
        (addr == 0x881A && value == 0xEB92) || 
        (addr == 0x8000 && value == 0x01) || 
        (addr == 0x8008 && value == 0xFC); 
*/
void DevControlFun(DevControl *pIp)
{
    ADDR_WRITE(0x881A, 0xEB92);
    ADDR_WRITE(0x8000, 0x01);
    ADDR_WRITE(0x8008, 0xFC);

    return ;
}
