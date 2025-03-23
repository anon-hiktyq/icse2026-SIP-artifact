#include "basicgetobjname.h"
void basicgetobjnameFun(void *p) 
{
    basicgetobjname *pIp = (basicgetobjname*)p;
  int pc = *(pIp->ppc);
  {const char * luaF_getlocalname_ret_0;IPCALL(luaF_getlocalname,ipluaF_getlocalname_0,.ret = luaF_getlocalname_ret_0);*pIp->name = luaF_getlocalname_ret_0;}
  if (*(pIp->name))  /* is a local? */
    pIp->ret =  "local";
  /* else try symbolic execution */
  {int findsetreg_ret_0;IPCALL(findsetreg,ipfindsetreg_0,.p = pIp->p,.lastpc = pc,.reg = pIp->reg,.ret = &findsetreg_ret_0);*pIp->ppc = pc = findsetreg_ret_0;}
  if (pc != -1) {  /* could find instruction? */
    Instruction i = (pIp->p)->code[pc];
    OpCode op;{op = GET_OPCODE(i);}
    switch (op) {
      case OP_MOVE: {
        int b;{b = GETARG_B(i);}  /* move from 'b' to 'a' */
        {if (b < GETARG_A(i))
          const char * basicgetobjname_ret_0;IPCALL(basicgetobjname,ipbasicgetobjname_0,.p = pIp->p,.ppc = pIp->ppc,.reg = b,.name = pIp->name,.ret = basicgetobjname_ret_0);pIp->ret =  basicgetobjname_ret_0; } /* get name for 'b' */
        break;
      }
      case OP_GETUPVAL: {
        {*pIp->name = upvalname(pIp->p, GETARG_B(i));}
        pIp->ret =  "upvalue";
      }
      case OP_LOADK: pIp->ret =  kname(p, GETARG_Bx(i), name);
      case OP_LOADKX: pIp->ret =  kname(p, GETARG_Ax(p->code[pc + 1]), name);
      default: break;
    }
  }
  pIp->ret =  NULL;  /* could not find reasonable name */
}