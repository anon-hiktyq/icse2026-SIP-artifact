
#include "DevControl.h"

/*@ axiomatic MemoryWrites {
      logic integer memory_write(integer addr, integer value);
      axiom write_effect:
      \forall integer addr, value; memory_write(addr, value) == value;
   }
*/

/*@ requires \valid(pIp);
    assigns \nothing;
    ensures memory_write(0x881A, 0xEB92) == 0xEB92;
    ensures memory_write(0x8000, 0x01) == 0x01;
    ensures memory_write(0x8008, 0xFC) == 0xFC;
*/
void DevControlFun(DevControl *pIp)
{
    /*@ assert \valid(pIp); */

    ADDR_WRITE(0x881A, 0xEB92);

    ADDR_WRITE(0x8000, 0x01);

    ADDR_WRITE(0x8008, 0xFC);

    return;
}
