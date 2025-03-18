#include "remarkupvals.h"
void remarkupvalsFun(void *p) 
{
    remarkupvals *pIp = (remarkupvals*)p;
  lua_State *thread;
  lua_State **p = pIp -> &g->twups;
  while ((thread = *p) != NULL) {
    if (!iswhite(thread) && thread->openupval != NULL)
      p = &thread->twups;  /* keep marked thread with upvalues in the list */
    else {  /* thread is not marked or without upvalues */
      UpVal *uv;
      lua_assert(!isold(thread) || thread->openupval == NULL);
      *p = thread->twups;  /* remove thread from the list */
      thread->twups = thread;  /* mark that it is out of list */
      for (uv = thread->openupval; uv != NULL; uv = uv->u.open.next) {
        lua_assert(getage(uv) <= getage(thread));
        if (!iswhite(uv)) {  /* upvalue already visited? */
          lua_assert(upisopen(uv) && isgray(uv));
          markvalue(pIp -> g, uv->v.p);  /* mark its value */
        }
      }
    }
  }
}