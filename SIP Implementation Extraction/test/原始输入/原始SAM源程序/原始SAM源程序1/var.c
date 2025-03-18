#include "ec.h"

/* -------------------------------��������-------------------------------------- */

/* ���������� (0.017453293)  */
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

/* ���ݰ�װ�� */
 float32	   VG[9][3] = { { 0.7672553f, -0.2792581f,  0.5773510f},
  								{-0.1417830f, -0.8040916f,  0.5773510f},
  								{-0.1417830f,  0.8040916f,  0.5773510f},
  								{ 0.7672553f,  0.2792581f,  0.5773510f},
  								{-0.6254722f, -0.5248335f,  0.5773510f},
  								{-0.6254722f,  0.5248335f,  0.5773510f},
  								{-0.4082480f, -0.7071063f, -0.5773510f},
  								{-0.4082480f,  0.7071063f, -0.5773510f},
  								{ 0.8164960f,  0.0f,       -0.5773510f}	};


/* ----------------------------------ȫ�ֱ������嶨��------------------------------- */

 unint08 						nouse ;					/*  �����ʹ�ñ���*/

 /***************************������***************************************************/
 volatile unint08       		countInt32ms;			/* 32ms������      */
 volatile unint08  				Count192ms; 			/* 192ms��������� */
 unint32           				countSate;
 unint32           				countPublic;
 unint32           				countMode;

 /***************************��־��****************************************************/
 unint16           				flgPRSAM;
 volatile unint08		  		flgGryoCalc;	        /* ���ݼ����־      */
 unint16           				flgNPC;
 volatile unint16       		flg160INT;				/* 160ms���ڼ�����־ */
 volatile unint32       		mFTdata;				/* FT����            */

/************************����**********************************************************/
 UInpIO1	     				mInpIO1;				/* IO1               */
 UInpIO2           				mInpIO2;				/* IO2               */
 UInpIO3	            		mInpIO3;				/* IO3               */
 UHealthwordHi       			mHealthwordHi;			/* �����ָ�          */
 UHealthwordLo       			mHealthwordLo;			/* �����ֵ�          */
 UPowerWord1        			mPowerword1;			/* ��Դ״̬��        */
 UPowerWord2        			mPowerword2;			/* ��Դ״̬��        */
 UPowerWord3        			mPowerword3;			/* ��Դ״̬��        */
 UPowerWord1 					mPCPowerword1;			/* ��Դ״̬�֣��̿أ�*/
 UPowerWord2 					mPCPowerword2;			/* ��Դ״̬�֣��̿أ�*/
 UPowerWord3 					mPCPowerword3;			/* ��Դ״̬�֣��̿أ�*/

 /**************************�ṹ��********************************************************/
 SAttitude         				mAttitude;				/* ��̬ */
 SDSSData          				mDSSData;
 SGyroData         				mGyroData;
 SController       				mController[3];
 SFratemodulator   				mModulator[3];			/* α����״̬��      */
 SThrDistribute    				mThrDistribute;
 SFWarning         				mFWarning;







