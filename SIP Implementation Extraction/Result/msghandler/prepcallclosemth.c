#include "prepcallclosemth.h"
void prepcallclosemthFun(void *p) 
{
    prepcallclosemth *pIp = (prepcallclosemth*)p;
  TValue uv;{uv = s2v(pIp->level);}  /* value being closed */
  TValue *errobj;
  switch ((pIp->status)) {
    case LUA_OK:
      (pIp->L)->top.p = (pIp->level) + 1;  /* call will be at this level */
      /* FALLTHROUGH */
    case CLOSEKTOP:  /* don't need to change top */
      errobj = NULL;  /* no error object */
      break;
    default:  /* 'luaD_seterrorobj' will set top to level + 2 */
      {errobj = s2v(pIp->level + 1);}  /* error object goes after 'uv' */
      {IPCALL(luaD_seterrorobj,ipluaD_seterrorobj_0);}  /* set error object */
      break;
  }
  {IPCALL(callclosemethod,ipcallclosemethod_0,.L = pIp->L,.obj = uv,.err = errobj,.yy = pIp->yy);}
}