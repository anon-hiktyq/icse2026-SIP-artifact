#if !defined(__COMMON_H__)
#define __COMMON_H__


#define IPCALL(IpName, InstName, ...) {IpName InstName = {.fun = IpName##Fun, __VA_ARGS__ };(InstName.fun(&InstName));}

#endif // __COMMON_H__