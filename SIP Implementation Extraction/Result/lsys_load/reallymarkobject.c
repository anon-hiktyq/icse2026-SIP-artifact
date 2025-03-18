#include "reallymarkobject.h"
void reallymarkobjectFun(void *p) 
{
    reallymarkobject *pIp = (reallymarkobject*)p;
  pIp -> g->GCmarked += {l_mem objsize_ret_0;IPCALL(objsize,ipobjsize_0,.o = pIp->o,.ret = &objsize_ret_0);}
  switch (pIp -> o->tt) {
    case LUA_VSHRSTR:
    case LUA_VLNGSTR: {
      set2black(pIp -> o);  /* nothing to visit */
      break;
    }
    case LUA_VUPVAL: {
      UpVal *uv = gco2upv(pIp -> o);
      if (upisopen(uv))
        set2gray(uv);  /* open upvalues are kept gray */
      else
        set2black(uv);  /* closed upvalues are visited here */
      markvalue(pIp -> g, uv->v.p);  /* mark its content */
      break;
    }
    case LUA_VUSERDATA: {
      Udata *u = gco2u(pIp -> o);
      if (u->nuvalue == 0) {  /* no user values? */
        {IPCALL(reallymarkobject,ipreallymarkobject_0,.g = pIp->g,.o = pIp->u->metatable);}  /* mark its metatable */
        set2black(u);  /* nothing else to mark */
        break;
      }
      /* else... */
    }  /* FALLTHROUGH */
    case LUA_VLCL: case LUA_VCCL: case LUA_VTABLE:
    case LUA_VTHREAD: case LUA_VPROTO: {
      linkobjgclist(pIp -> o, pIp -> g->gray);  /* to be visited later */
      break;
    }
    default: lua_assert(0); break;
  }
}