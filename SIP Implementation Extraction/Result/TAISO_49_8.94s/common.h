#ifndef COMMON_H
#define COMMON_H

/* standard library */
#include <math.h>

typedef void (*Fun)(void *);
#define IPCALL(IpName, InstName, ...) {IpName InstName = {.fun = IpName##Fun, __VA_ARGS__ };(InstName.fun(&InstName));}


#endif /* COMMON_H */
