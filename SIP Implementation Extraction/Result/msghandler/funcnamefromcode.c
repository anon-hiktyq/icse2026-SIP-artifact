#include "funcnamefromcode.h"
void funcnamefromcodeFun(void *p) 
{
    funcnamefromcode *pIp = (funcnamefromcode*)p;

  TMS tm = (TMS)0;  /* (initial value avoids warnings) */
  Instruction i = pIp -> p->code[pIp -> pc];  /* calling instruction */
  switch (GET_OPCODE(i)) {
    case OP_CALL:
    case OP_TAILCALL:
      pIp -> {const char * getobjname_ret_0;IPCALL(getobjname,ipgetobjname_0,.pIp->p = pIp->pIp->p,.lastpc = pIp->pc,.reg = GETARG_A(i),.pIp->name = pIp->pIp->name,.pIp->ret = pIp->getobjname_ret_0);}name); /* get function pIp -> name */
    case OP_TFORCALL: {  /* for iterator */
      pIp -> *name = "for iterator";
       pIp -> ret = "for iterator";
    }
    /* other instructions can do calls through metamethods */
    case OP_SELF: case OP_GETTABUP: case OP_GETTABLE:
    case OP_GETI: case OP_GETFIELD:
      tm = TM_INDEX;
      break;
    case OP_SETTABUP: case OP_SETTABLE: case OP_SETI: case OP_SETFIELD:
      tm = TM_NEWINDEX;
      break;
    case OP_MMBIN: case OP_MMBINI: case OP_MMBINK: {
      tm = cast(TMS, GETARG_C(i));
      break;
    }
    case OP_UNM: tm = TM_UNM; break;
    case OP_BNOT: tm = TM_BNOT; break;
    case OP_LEN: tm = TM_LEN; break;
    case OP_CONCAT: tm = TM_CONCAT; break;
    case OP_EQ: tm = TM_EQ; break;
    /* no cases for OP_EQI and OP_EQK, as they don't call metamethods */
    case OP_LT: case OP_LTI: case OP_GTI: tm = TM_LT; break;
    case OP_LE: case OP_LEI: case OP_GEI: tm = TM_LE; break;
    case OP_CLOSE: case OP_RETURN: tm = TM_CLOSE; break;
    default:
      pIp -> ret = NULL; /* cannot find a reasonable pIp -> name */
  }
  pIp -> *name = getshrstr(G(pIp -> L)->tmname[tm]) + 2;
  pIp -> ret = "metamethod";
}