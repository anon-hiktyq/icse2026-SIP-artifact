
#include "DevControl.h"

/*@ axiomatic MemoryOperations {
      logic integer memory_value{L}(integer addr) reads \at(addr, L);
      axiom addr_write_axiom:
        \forall integer addr, value; \at(ADDR_WRITE(addr, value), Pre) ==>
          \at(memory_value(addr), Post) == value;
    }
*/

/*@ requires \valid(pIp);
    assigns memory_value(0x881A), memory_value(0x8000), memory_value(0x8008);
    ensures memory_value(0x881A) == 0xEB92;
    ensures memory_value(0x8000) == 0x01;
    ensures memory_value(0x8008) == 0xFC;
*/
void DevControlFun(DevControl *pIp)
{
    ADDR_WRITE(0x881A, 0xEB92);
    ADDR_WRITE(0x8000, 0x01);
    ADDR_WRITE(0x8008, 0xFC);

    return ;
}
