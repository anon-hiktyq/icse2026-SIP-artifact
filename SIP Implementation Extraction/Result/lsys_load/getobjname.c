#include "getobjname.h"
void getobjnameFun(void *p) 
{
    getobjname *pIp = (getobjname*)p;
  const char kind;{const char * basicgetobjname_ret_0; IPCALL(basicgetobjname,ipbasicgetobjname_0,.p = pIp->p,.ppc = pIp->&lastpc,.reg = pIp->reg,.name = pIp->name,.ret = basicgetobjname_ret_0);kind = basicgetobjname_ret_0;}
  if (kind != NULL)
    pIp->ret =  kind;
  else if ((pIp->lastpc) != -1) {  /* could find instruction? */
    Instruction i = (pIp->p)->code[(pIp->lastpc)];
    OpCode op;{op = GET_OPCODE(i);}
    switch (op) {
      case OP_GETTABUP: {
        int k;{k = GETARG_C(i);}  /* key index */
        {const char * kname_ret_0;IPCALL(kname,ipkname_0,.p = pIp->p,.index = k,.name = pIp->name,.ret = kname_ret_0);kname_ret_0;}
        const char * isEnv_ret_0;IPCALL(isEnv,ipisEnv_0,.p = pIp->p,.pc = pIp->lastpc,.i = i,.isup = 1,.ret = isEnv_ret_0);pIp->ret =  isEnv_ret_0;
      }
      case OP_GETTABLE: {
        int k;{k = GETARG_C(i);}  /* key index */
        {IPCALL(rname,iprname_0,.p = pIp->p,.pc = pIp->lastpc,.c = k,.name = pIp->name);}
        const char * isEnv_ret_1;IPCALL(isEnv,ipisEnv_1,.p = pIp->p,.pc = pIp->lastpc,.i = i,.isup = 0,.ret = isEnv_ret_1);pIp->ret =  isEnv_ret_1;
      }
      case OP_GETI: {
        *(pIp->name) = "integer index";
        pIp->ret =  "field";
      }
      case OP_GETFIELD: {
        int k;{k = GETARG_C(i);}  /* key index */
        {const char * kname_ret_1;IPCALL(kname,ipkname_1,.p = pIp->p,.index = k,.name = pIp->name,.ret = kname_ret_1);kname_ret_1;}
        const char * isEnv_ret_2;IPCALL(isEnv,ipisEnv_2,.p = pIp->p,.pc = pIp->lastpc,.i = i,.isup = 0,.ret = isEnv_ret_2);pIp->ret =  isEnv_ret_2;
      }
      case OP_SELF: {
        int k;{k = GETARG_C(i);}  /* key index */
        {const char * kname_ret_2;IPCALL(kname,ipkname_2,.p = pIp->p,.index = k,.name = pIp->name,.ret = kname_ret_2);kname_ret_2;}
        pIp->ret =  "method";
      }
      default: break;  /* go through to return NULL */
    }
  }
  pIp->ret =  NULL;  /* could not find reasonable name */
}