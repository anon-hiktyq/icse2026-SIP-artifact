#include "basicgetobjname.h"
void basicgetobjnameFun(void *p) 
{
    basicgetobjname *pIp = (basicgetobjname*)p;

  int pc = pIp -> *ppc;
  {const char * luaF_getlocalname_ret_5;IPCALL(luaF_getlocalname,ipluaF_getlocalname_0,.ret = pIp->luaF_getlocalname_ret_5);*pIp->name = luaF_getlocalname_ret_5;}
  if (pIp -> *name)  /* is a local? */
    pIp -> ret = "local";
  /* else try symbolic execution */
  {int findsetreg_ret_4;IPCALL(findsetreg,ipfindsetreg_0,.p = pIp->p,.lastpc = pc,.reg = pIp->reg,.ret = pIp->&findsetreg_ret_4);*pIp->ppc = pc = findsetreg_ret_4;}
  if (pc != -1) {  /* could find instruction? */
    Instruction i = pIp -> p->code[pc];
    OpCode op = GET_OPCODE(i);
    switch (op) {
      case OP_MOVE: {
        int b = GETARG_B(i);  /* move from 'b' to 'a' */
        if (b < GETARG_A(i))
          pIp -> {const char * basicgetobjname_ret_3;IPCALL(basicgetobjname,ipbasicgetobjname_0,.p = pIp->p,.ppc = pIp->ppc,.reg = pIp->b,.name = pIp->name,.ret = pIp->basicgetobjname_ret_3);}name); /* get pIp -> name for 'b' */
        break;
      }
      case OP_GETUPVAL: {
        {const char * upvalname_ret_2;IPCALL(upvalname,ipupvalname_0,.pIp->p = pIp->pIp->p,.uv = GETARG_B(i),.pIp->ret = pIp->upvalname_ret_2);*pIp->name = upvalname_ret_2;}
        pIp -> ret = "upvalue";
      }
      case OP_LOADK: return {const char * kname_ret_1;IPCALL(kname,ipkname_1,.pIp->p = pIp->pIp->p,.index = GETARG_Bx(i),.pIp->name = pIp->pIp->name,.pIp->ret = pIp->kname_ret_1);}
      case OP_LOADKX: return {const char * kname_ret_0;IPCALL(kname,ipkname_0,.pIp->p = pIp->pIp->p,.index = GETARG_Ax(pIp->p->code[pc + 1]),.pIp->name = pIp->pIp->name,.pIp->ret = pIp->kname_ret_0);}
      default: break;
    }
  }
  pIp -> ret = NULL; /* could not find reasonable pIp -> name */
}