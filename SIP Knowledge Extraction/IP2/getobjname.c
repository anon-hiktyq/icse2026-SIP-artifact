#include "getobjname.h"
void getobjnameFun(void *p) 
{
    getobjname *pIp = (getobjname*)p;

  const char *kind;{const char * basicgetobjname_ret_3;IPCALL(basicgetobjname,ipbasicgetobjname_0,.p = pIp->p,.ppc = &lastpc,.reg = pIp->reg,.name = pIp->name,.ret = pIp->basicgetobjname_ret_3);*kind = basicgetobjname_ret_3}
  if (kind != NULL)
    pIp -> ret = kind;
  else if (pIp -> lastpc != -1) {  /* could find instruction? */
    Instruction i = pIp -> p->code[pIp -> lastpc];
    OpCode op = GET_OPCODE(i);
    switch (op) {
      case OP_GETTABUP: {
        int k = GETARG_C(i);  /* key index */
        {const char * kname_ret_2;IPCALL(kname,ipkname_2,.p = pIp->p,.index = k,.name = pIp->name,.ret = pIp->kname_ret_2);}
        pIp -> ret = isEnv(p, lastpc, i, 1);
      }
      case OP_GETTABLE: {
        int k = GETARG_C(i);  /* key index */
        {IPCALL(rname,iprname_0,.p = pIp->p,.pc = lastpc,.c = k,.name = pIp->name);}
        pIp -> ret = isEnv(p, lastpc, i, 0);
      }
      case OP_GETI: {
        pIp -> *name = "integer index";
        pIp -> ret = "field";
      }
      case OP_GETFIELD: {
        int k = GETARG_C(i);  /* key index */
        {const char * kname_ret_1;IPCALL(kname,ipkname_1,.p = pIp->p,.index = k,.name = pIp->name,.ret = pIp->kname_ret_1);}
        pIp -> ret = isEnv(p, lastpc, i, 0);
      }
      case OP_SELF: {
        int k = GETARG_C(i);  /* key index */
        {const char * kname_ret_0;IPCALL(kname,ipkname_0,.p = pIp->p,.index = k,.name = pIp->name,.ret = pIp->kname_ret_0);}
        pIp -> ret = "method";
      }
      default: break;  /* go through to return NULL */
    }
  }
  pIp -> ret = NULL; /* could not find reasonable pIp -> name */
}