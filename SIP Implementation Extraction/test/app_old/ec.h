
#include "ma.h"
#include "ty.h"

extern SControllerParam  CTRL_PARAM_SAM[3];
extern unint32  countSate;
extern unint32  countPublic;
extern unint32  countMode; 					/* 控制周期计数器 */
extern unint16  flgPRSAM;						/* 搜索太阳失效标志 */
extern unint16  flgNPC;						/* 程控标志 */
extern unint16  flg128INT;
extern unint08  GC;
extern volatile unint08	 	    Count192ms;
extern volatile unint08	        flgGryoCalc;
extern volatile unint16  	    flg160INT;		/* 160ms周期计数标志 */
extern volatile unint08        countInt32ms;   /* 32ms中断计数器 */
extern volatile unint32        mFTdata;		/* 重要数据 */
extern  float32 	     	    VG[9][3];   	/* 陀螺安装阵 */
extern  unint08 	           nouse ;			/* 无用 */
extern  UInpIO1 	           mInpIO1;		/* IO1板 */
extern  UInpIO2 	           mInpIO2;		/* IO2板 */
extern  UInpIO3 	           mInpIO3;		/* IO3板 */
extern  UHealthwordHi          mHealthwordHi;	/* 健康字高 */
extern  UHealthwordLo          mHealthwordLo;	/* 健康字低 */
extern  UPowerWord1            mPowerword1;	/* 电源字 */
extern  UPowerWord2            mPowerword2;	/* 电源字 */
extern  UPowerWord3            mPowerword3;	/* 电源字 */
extern  UPowerWord1            mPCPowerword1;	/* 程控电源字 */
extern  UPowerWord2            mPCPowerword2;	/* 程控电源字 */
extern  UPowerWord3            mPCPowerword3;	/* 程控电源字 */
/*************************************结构体********************************************/
extern  SAttitude              mAttitude;		/* 姿态 */
extern  SDSSData               mDSSData;		/* 数太数据 */
extern  SGyroData           	mGyroData;		/* 陀螺数据 */
extern  SController            mController[3];	/* 控制器 */
extern  SFratemodulator        mModulator[3];	/* 伪速率状态量 */
extern  SThrDistribute         mThrDistribute;	/* 软件喷气变量 */
extern  SFWarning              mFWarning;

/* --------函数声明-------- */
extern void AppInit(void);
extern void ClearRAM(void);
extern void ClearDog(void);
extern void ProgramControl(void);
extern void ModeControl(void);
extern void SAMSubModeDamp(void);
extern void SAMSubModePitch(void);
extern void SAMSubModeRoll(void);
extern void SAMSubModeCruise(void);
extern void FaultJudgeProceed(void);
extern void Input(void);
extern void GyroPick(void);
extern void GyroProceed(void);
extern void SavePowerWord(void);
extern void Inputproceed(void);
extern void LimitControllerInput(void);
extern void ThreeAxisController(void);
extern void PseudoRateModulator(SFratemodulator *pModulator, float32 h1);
extern void ThrusterCtrlLogic(void);
extern void SwitchSS(void);
extern void ThrABAutoChoose(void);
extern void SoftFaultJudgeSP(void);
extern void SoftFaultProceedSP(void);
extern void NoctrlJudge(void);
extern float32 DiviationToFloat(unint16 input, unint16 mask, unint16 offset, float32 LSB);
extern float32 TripleFabsMax(float32 fx1, float32 fy2, float32 fz3);
extern float32 LimitFloat32(float32 fin, float32 fbound);
extern float32 ModPNHP(float32 x, float32 halfperiod);
extern unint32 FTRead(void);
extern unint32 Tr32Uint(unint32 volatile  *pA, unint32 volatile  *pB, unint32 volatile  *pC);
extern unint08 Tr32Uint08(unint08 volatile  *pA, unint08 volatile  *pB, unint08 volatile  *pC);
extern float32 Tr32Float(float32 volatile  *pA, float32 volatile  *pB, float32 volatile  *pC);
extern void Delay(unint16 delaytime);
extern void GPIOInit(void);
extern void Pulse_Out(void);
extern void CalculateGyroRs(void);
extern void CalculateGyroDg(void);
extern unint08 MatrixInv33F(float32 *inv, const float32 *src);
extern void MatrixVectorMul(float32 *a, float32 *b, float32 *c, unint08 m, unint08 n);
extern void GyroStateSet(void);
extern void GyroChoose(void);
extern void MatrixTran(float32 *tran, const float32 *mat, unint08 nrow, unint08 ncol);
extern void MatrixMulti(float32 *product,const float32 *faciend,const float32 *multiplier, unint08 nrow, unint08 nrc, unint08 ncol);









