#include "cleargraylists.h"
void cleargraylistsFun(void *p) 
{
    cleargraylists *pIp = (cleargraylists*)p;
  (pIp->g)->gray = (pIp->g)->grayagain = NULL;
  (pIp->g)->weak = (pIp->g)->allweak = (pIp->g)->ephemeron = NULL;
}