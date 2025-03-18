#if !defined(__FINDSETREG_H__)
#define __FINDSETREG_H__

#include "common.h"
#include "filterpc.h"

#ifndef _GET_OPCODE_
	#define GET_OPCODE (cast(OpCode, ((i)>>POS_OP) & MASK1(SIZE_OP,0)))
#endif

#ifndef _GETARG_A_
	#define GETARG_A getarg(i, POS_A, SIZE_A)
#endif

#ifndef _GETARG_B_
	#define GETARG_B check_exp(checkopm(i, iABC), getarg(i, POS_B, SIZE_B))
#endif

#ifndef _GETARG_SJ_
	#define GETARG_sJ check_exp(checkopm(i, isJ), getarg(i, POS_sJ, SIZE_sJ) - OFFSET_sJ)
#endif

#ifndef _TESTAMODE_
	#define testAMode (luaP_opmodes[m] & (1 << 3))
#endif

#ifndef _TESTMMMODE_
	#define testMMMode (luaP_opmodes[m] & (1 << 7))
#endif

#ifndef _LU_BYTE_
	typedef unsigned char lu_byte;
#endif

typedef l_uint32 Instruction;
#ifndef _PROTO_
	struct Proto {
	  CommonHeader;
	  lu_byte numparams;  /* number of fixed (named) parameters */
	  lu_byte flag;
	  lu_byte maxstacksize;  /* number of registers needed by this function */
	  int sizeupvalues;  /* size of 'upvalues' */
	  int sizek;  /* size of 'k' */
	  int sizecode;
	  int sizelineinfo;
	  int sizep;  /* size of 'p' */
	  int sizelocvars;
	  int sizeabslineinfo;  /* size of 'abslineinfo' */
	  int linedefined;  /* debug information  */
	  int lastlinedefined;  /* debug information  */
	  TValue *k;  /* constants used by the function */
	  Instruction *code;  /* opcodes */
	  struct Proto **p;  /* functions defined inside the function */
	  Upvaldesc *upvalues;  /* upvalue information */
	  ls_byte *lineinfo;  /* information about source lines (debug information) */
	  AbsLineInfo *abslineinfo;  /* idem */
	  LocVar *locvars;  /* information about local variables (debug information) */
	  TString  *source;  /* used for debug information */
	  GCObject *gclist;
	};
#endif

#ifndef _OPCODE_
	enum {
	/*----------------------------------------------------------------------
	  name		args	description
	------------------------------------------------------------------------*/
	OP_MOVE,/*	A B	R[A] := R[B]					*/
	OP_LOADI,/*	A sBx	R[A] := sBx					*/
	OP_LOADF,/*	A sBx	R[A] := (lua_Number)sBx				*/
	OP_LOADK,/*	A Bx	R[A] := K[Bx]					*/
	OP_LOADKX,/*	A	R[A] := K[extra arg]				*/
	OP_LOADFALSE,/*	A	R[A] := false					*/
	OP_LFALSESKIP,/*A	R[A] := false; pc++	(*)			*/
	OP_LOADTRUE,/*	A	R[A] := true					*/
	OP_LOADNIL,/*	A B	R[A], R[A+1], ..., R[A+B] := nil		*/
	OP_GETUPVAL,/*	A B	R[A] := UpValue[B]				*/
	OP_SETUPVAL,/*	A B	UpValue[B] := R[A]				*/
	
	OP_GETTABUP,/*	A B C	R[A] := UpValue[B][K[C]:shortstring]		*/
	OP_GETTABLE,/*	A B C	R[A] := R[B][R[C]]				*/
	OP_GETI,/*	A B C	R[A] := R[B][C]					*/
	OP_GETFIELD,/*	A B C	R[A] := R[B][K[C]:shortstring]			*/
	
	OP_SETTABUP,/*	A B C	UpValue[A][K[B]:shortstring] := RK(C)		*/
	OP_SETTABLE,/*	A B C	R[A][R[B]] := RK(C)				*/
	OP_SETI,/*	A B C	R[A][B] := RK(C)				*/
	OP_SETFIELD,/*	A B C	R[A][K[B]:shortstring] := RK(C)			*/
	
	OP_NEWTABLE,/*	A B C k	R[A] := {}					*/
	
	OP_SELF,/*	A B C	R[A+1] := R[B]; R[A] := R[B][K[C]:shortstring]	*/
	
	OP_ADDI,/*	A B sC	R[A] := R[B] + sC				*/
	
	OP_ADDK,/*	A B C	R[A] := R[B] + K[C]:number			*/
	OP_SUBK,/*	A B C	R[A] := R[B] - K[C]:number			*/
	OP_MULK,/*	A B C	R[A] := R[B] * K[C]:number			*/
	OP_MODK,/*	A B C	R[A] := R[B] % K[C]:number			*/
	OP_POWK,/*	A B C	R[A] := R[B] ^ K[C]:number			*/
	OP_DIVK,/*	A B C	R[A] := R[B] / K[C]:number			*/
	OP_IDIVK,/*	A B C	R[A] := R[B] // K[C]:number			*/
	
	OP_BANDK,/*	A B C	R[A] := R[B] & K[C]:integer			*/
	OP_BORK,/*	A B C	R[A] := R[B] | K[C]:integer			*/
	OP_BXORK,/*	A B C	R[A] := R[B] ~ K[C]:integer			*/
	
	OP_SHRI,/*	A B sC	R[A] := R[B] >> sC				*/
	OP_SHLI,/*	A B sC	R[A] := sC << R[B]				*/
	
	OP_ADD,/*	A B C	R[A] := R[B] + R[C]				*/
	OP_SUB,/*	A B C	R[A] := R[B] - R[C]				*/
	OP_MUL,/*	A B C	R[A] := R[B] * R[C]				*/
	OP_MOD,/*	A B C	R[A] := R[B] % R[C]				*/
	OP_POW,/*	A B C	R[A] := R[B] ^ R[C]				*/
	OP_DIV,/*	A B C	R[A] := R[B] / R[C]				*/
	OP_IDIV,/*	A B C	R[A] := R[B] // R[C]				*/
	
	OP_BAND,/*	A B C	R[A] := R[B] & R[C]				*/
	OP_BOR,/*	A B C	R[A] := R[B] | R[C]				*/
	OP_BXOR,/*	A B C	R[A] := R[B] ~ R[C]				*/
	OP_SHL,/*	A B C	R[A] := R[B] << R[C]				*/
	OP_SHR,/*	A B C	R[A] := R[B] >> R[C]				*/
	
	OP_MMBIN,/*	A B C	call C metamethod over R[A] and R[B]	(*)	*/
	OP_MMBINI,/*	A sB C k	call C metamethod over R[A] and sB	*/
	OP_MMBINK,/*	A B C k		call C metamethod over R[A] and K[B]	*/
	
	OP_UNM,/*	A B	R[A] := -R[B]					*/
	OP_BNOT,/*	A B	R[A] := ~R[B]					*/
	OP_NOT,/*	A B	R[A] := not R[B]				*/
	OP_LEN,/*	A B	R[A] := #R[B] (length operator)			*/
	
	OP_CONCAT,/*	A B	R[A] := R[A].. ... ..R[A + B - 1]		*/
	
	OP_CLOSE,/*	A	close all upvalues >= R[A]			*/
	OP_TBC,/*	A	mark variable A "to be closed"			*/
	OP_JMP,/*	sJ	pc += sJ					*/
	OP_EQ,/*	A B k	if ((R[A] == R[B]) ~= k) then pc++		*/
	OP_LT,/*	A B k	if ((R[A] <  R[B]) ~= k) then pc++		*/
	OP_LE,/*	A B k	if ((R[A] <= R[B]) ~= k) then pc++		*/
	
	OP_EQK,/*	A B k	if ((R[A] == K[B]) ~= k) then pc++		*/
	OP_EQI,/*	A sB k	if ((R[A] == sB) ~= k) then pc++		*/
	OP_LTI,/*	A sB k	if ((R[A] < sB) ~= k) then pc++			*/
	OP_LEI,/*	A sB k	if ((R[A] <= sB) ~= k) then pc++		*/
	OP_GTI,/*	A sB k	if ((R[A] > sB) ~= k) then pc++			*/
	OP_GEI,/*	A sB k	if ((R[A] >= sB) ~= k) then pc++		*/
	
	OP_TEST,/*	A k	if (not R[A] == k) then pc++			*/
	OP_TESTSET,/*	A B k	if (not R[B] == k) then pc++ else R[A] := R[B] (*) */
	
	OP_CALL,/*	A B C	R[A], ... ,R[A+C-2] := R[A](R[A+1], ... ,R[A+B-1]) */
	OP_TAILCALL,/*	A B C k	return R[A](R[A+1], ... ,R[A+B-1])		*/
	
	OP_RETURN,/*	A B C k	return R[A], ... ,R[A+B-2]	(see note)	*/
	OP_RETURN0,/*		return						*/
	OP_RETURN1,/*	A	return R[A]					*/
	
	OP_FORLOOP,/*	A Bx	update counters; if loop continues then pc-=Bx; */
	OP_FORPREP,/*	A Bx	<check values and prepare counters>;
	                        if not to run then pc+=Bx+1;			*/
	
	OP_TFORPREP,/*	A Bx	create upvalue for R[A + 3]; pc+=Bx		*/
	OP_TFORCALL,/*	A C	R[A+4], ... ,R[A+3+C] := R[A](R[A+1], R[A+2]);	*/
	OP_TFORLOOP,/*	A Bx	if R[A+2] ~= nil then { R[A]=R[A+2]; pc -= Bx }	*/
	
	OP_SETLIST,/*	A vB vC k	R[A][vC+i] := R[A+i], 1 <= i <= vB	*/
	
	OP_CLOSURE,/*	A Bx	R[A] := closure(KPROTO[Bx])			*/
	
	OP_VARARG,/*	A C	R[A], R[A+1], ..., R[A+C-2] = vararg		*/
	
	OP_VARARGPREP,/*A	(adjust vararg parameters)			*/
	
	OP_EXTRAARG/*	Ax	extra (larger) argument for previous opcode	*/
	};
#endif


void findsetregFun(void *p);

typedef struct __findsetreg
{
	/* Functional Interface */
	Fun			fun;
	/* Input Variables */
	const Proto*			p;
	int			lastpc;
	int			reg;
	/* Output Variables */
	int			setreg;
	int*			ret;
	/* In&Output Variables */
	/* Statement Variables*/
	/* Argument Variables */
} findsetreg;

#endif // __FINDSETREG_H__