#include "convergeephemerons.h"
void convergeephemeronsFun(void *p) 
{
    convergeephemerons *pIp = (convergeephemerons*)p;
  int changed;
  int dir = 0;
  do {
    GCObject *w;
    GCObject *next = (pIp->g)->ephemeron;  /* get ephemeron list */
    (pIp->g)->ephemeron = NULL;  /* tables may return to this list when traversed */
    changed = 0;
    while ((w = next) != NULL) {  /* for each ephemeron table */
      Table h;{h = gco2t(w);}
      next = h->gclist;  /* list is rebuilt during loop */
      {nw2black(h);}  /* out of the list (for now) */
      {int traverseephemeron_ret_0;IPCALL(traverseephemeron,iptraverseephemeron_0,.g = pIp->g,.h = h,.inv = dir,.ret = &traverseephemeron_ret_0);if (traverseephemeron_ret_0) {  /* marked some value? */
        {IPCALL(propagateall,ippropagateall_0,.g = pIp->g);}  /* propagate changes */
        changed = 1;  /* will have to revisit all ephemeron tables */
      }}
    }
    dir = !dir;  /* invert direction next time */
  } while (changed);  /* repeat until no more changes */
}