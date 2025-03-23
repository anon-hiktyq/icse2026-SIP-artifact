#include "luaP_isIT.h"
void luaP_isITFun(void *p) 
{
    luaP_isIT *pIp = (luaP_isIT*)p;
  OpCode op;{op = GET_OPCODE(pIp->i);}
  switch (op) {
    case OP_SETLIST:
      *(pIp->ret) =  testITMode(GET_OPCODE(i)) && GETARG_vB(i) == 0;
    default:
      *(pIp->ret) =  testITMode(GET_OPCODE(i)) && GETARG_B(i) == 0;
  }
}