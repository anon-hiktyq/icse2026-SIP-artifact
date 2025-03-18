#ifndef COMMON_H
#define COMMON_H

/* standard library */
#include <assert.h>
#include <ctype.h>
#include <dlfcn.h>
#include <errno.h>
#include <float.h>
#include <io.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>


typedef void (*Fun)(void *);#define IPCALL(IpName, InstName, ...) {IpName InstName = {.fun = IpName##Fun, __VA_ARGS__ };(InstName.fun(&InstName));}

#endif /* COMMON_H */
