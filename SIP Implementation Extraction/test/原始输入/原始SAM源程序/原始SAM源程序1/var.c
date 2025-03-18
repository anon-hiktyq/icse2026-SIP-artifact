#include "ec.h"

/* -------------------------------常数定义-------------------------------------- */

/* 控制器参数 (0.017453293)  */
/**********************************************************************************
  32.5 (0.05672320225)       19.6(0.3420845428)                   0
  366.0                      220.6                              218.5
  0.568                      0.342                              0.339
***********************************************************************************/
SControllerParam    CTRL_PARAM_SAM[3] =
{
    {0.567232f,	6.387905f,	0.568f},
    {0.342085f,	3.850196f,	0.342f},
    {0.0f     ,	3.813545f,	0.339f}
};

/* 陀螺安装阵 */
 float32	   VG[9][3] = { { 0.7672553f, -0.2792581f,  0.5773510f},
  								{-0.1417830f, -0.8040916f,  0.5773510f},
  								{-0.1417830f,  0.8040916f,  0.5773510f},
  								{ 0.7672553f,  0.2792581f,  0.5773510f},
  								{-0.6254722f, -0.5248335f,  0.5773510f},
  								{-0.6254722f,  0.5248335f,  0.5773510f},
  								{-0.4082480f, -0.7071063f, -0.5773510f},
  								{-0.4082480f,  0.7071063f, -0.5773510f},
  								{ 0.8164960f,  0.0f,       -0.5773510f}	};


/* ----------------------------------全局变量定义定义------------------------------- */

 unint08 						nouse ;					/*  空语句使用变量*/

 /***************************计数器***************************************************/
 volatile unint08       		countInt32ms;			/* 32ms计数器      */
 volatile unint08  				Count192ms; 			/* 192ms脉冲计数器 */
 unint32           				countSate;
 unint32           				countPublic;
 unint32           				countMode;

 /***************************标志量****************************************************/
 unint16           				flgPRSAM;
 volatile unint08		  		flgGryoCalc;	        /* 陀螺计算标志      */
 unint16           				flgNPC;
 volatile unint16       		flg160INT;				/* 160ms周期计数标志 */
 volatile unint32       		mFTdata;				/* FT数据            */

/************************联合**********************************************************/
 UInpIO1	     				mInpIO1;				/* IO1               */
 UInpIO2           				mInpIO2;				/* IO2               */
 UInpIO3	            		mInpIO3;				/* IO3               */
 UHealthwordHi       			mHealthwordHi;			/* 健康字高          */
 UHealthwordLo       			mHealthwordLo;			/* 健康字低          */
 UPowerWord1        			mPowerword1;			/* 电源状态字        */
 UPowerWord2        			mPowerword2;			/* 电源状态字        */
 UPowerWord3        			mPowerword3;			/* 电源状态字        */
 UPowerWord1 					mPCPowerword1;			/* 电源状态字（程控）*/
 UPowerWord2 					mPCPowerword2;			/* 电源状态字（程控）*/
 UPowerWord3 					mPCPowerword3;			/* 电源状态字（程控）*/

 /**************************结构体********************************************************/
 SAttitude         				mAttitude;				/* 姿态 */
 SDSSData          				mDSSData;
 SGyroData         				mGyroData;
 SController       				mController[3];
 SFratemodulator   				mModulator[3];			/* 伪速率状态量      */
 SThrDistribute    				mThrDistribute;
 SFWarning         				mFWarning;







