#include "DevControl.h"
void DevControlFun(void *p)
{
    DevControl *pIp = (DevControl*)p;

	ADDR_WRITE(0x881A, 0xEB92);

	ADDR_WRITE(0x8000, 0x01);

	ADDR_WRITE(0x8008, 0xFC);

	return ;
}