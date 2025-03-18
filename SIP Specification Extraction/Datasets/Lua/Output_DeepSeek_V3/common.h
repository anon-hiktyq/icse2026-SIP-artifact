#if !defined(__COMMON_H__)
#define __COMMON_H__

#endif // __COMMON_H__

#include <stddef.h>

#define IPCALL(IpName, InstName, ...) {IpName InstName = {.fun = IpName##Fun, __VA_ARGS__ };(InstName.fun(&InstName));}