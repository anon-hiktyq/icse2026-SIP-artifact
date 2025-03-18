#include "findsetreg.h"
void findsetregFun(void *p) 
{
    findsetreg *pIp = (findsetreg*)p;
  int pc;
  int pIp -> setreg = -1;  /* keep last instruction that changed 'pIp -> reg' */
  int jmptarget = 0;  /* any code before this address is conditional */
  if (testMMMode(GET_OPCODE(pIp -> p->code[pIp -> lastpc])))
    pIp -> lastpc--;  /* previous instruction was not actually executed */
  for (pc = 0; pc < pIp -> lastpc; pc++) {
    Instruction i = pIp -> p->code[pc];
    OpCode op = GET_OPCODE(i);
    int a = GETARG_A(i);
    int change;  /* true if current instruction changed 'pIp -> reg' */
    switch (op) {
      case OP_LOADNIL: {  /* set registers from 'a' to 'a+b' */
        int b = GETARG_B(i);
        change = (a <= pIp -> reg && pIp -> reg <= a + b);
        break;
      }
      case OP_TFORCALL: {  /* affect all regs above its base */
        change = (pIp -> reg >= a + 2);
        break;
      }
      case OP_CALL:
      case OP_TAILCALL: {  /* affect all registers above base */
        change = (pIp -> reg >= a);
        break;
      }
      case OP_JMP: {  /* doesn't change registers, but changes 'jmptarget' */
        int b = GETARG_sJ(i);
        int dest = pc + 1 + b;
        /* jump does not skip 'lastpc' and is larger than current one? */
        if (dest <= pIp -> lastpc && dest > jmptarget)
          jmptarget = dest;  /* update 'jmptarget' */
        change = 0;
        break;
      }
      default:  /* any instruction that sets A */
        change = (testAMode(op) && pIp -> reg == a);
        break;
    }
    if (change)
      pIp -> setreg = {int filterpc_ret_0;IPCALL(filterpc,ipfilterpc_0,.pc = pc,.jmptarget = jmptarget,.ret = pIp->&filterpc_ret_0);}
  }
  *(pIp -> ret) = setreg;
}