
#ifndef GNC_INPUT_H
#define GNC_INPUT_H

#include "std_basal.h"
#include "config.h"

/* 判断设备已加电 */
#define DEV_IS_POWERON(DEV_TABLE)	   (DEV_TABLE.flgPower != DEV_INVALID)

/* 判断设备是健康 */
#define DEV_IS_HEALTH(DEV_TABLE)		(DEV_TABLE.flgHealth != DEV_INVALID)

/* 判断设备处于当班态 */
#define DEV_IS_ONDUTY(DEV_TABLE)		(DEV_TABLE.flgDuty != DEV_INVALID)

/* 判断设备是否允许自主刷新设备状态表 */
#define DEV_IS_UPDATA(DEV_TABLE)		(DEV_TABLE.flgUpdata != DEV_INVALID)

/* 判断设备处于未加电 */
#define DEV_NOT_POWERON(DEV_TABLE)	  (DEV_TABLE.flgPower == DEV_INVALID)

/* 判断设备处于非健康 */
#define DEV_NOT_HEALTH(DEV_TABLE)	   (DEV_TABLE.flgHealth == DEV_INVALID)

/* 判断设备处于非当班态 */
#define DEV_NOT_ONDUTY(DEV_TABLE)	   (DEV_TABLE.flgDuty == DEV_INVALID)

/* 获得设备加电状态 */
#define DEV_POWER_GET(DEV_TABLE)		(DEV_TABLE.flgPower)

/* 获得设备健康状态 */
#define DEV_HEALTH_GET(DEV_TABLE)	   (DEV_TABLE.flgHealth)

/* 获得设备当班状态 */
#define DEV_DUTY_GET(DEV_TABLE)		 (DEV_TABLE.flgDuty)

/* 设置设备加电状态 */
#define DEV_POWER_SET(DEV_TABLE, pw)	(DEV_TABLE.flgPower = (pw))

/* 设置设备健康状态 */
#define DEV_HEALTH_SET(DEV_TABLE, ht)   (DEV_TABLE.flgHealth = (ht))

/* 设置设备当班状态 */
#define DEV_DUTY_SET(DEV_TABLE, duty)   (DEV_TABLE.flgDuty = (duty))

/* 设备状态 */
#define DEV_ONDUTY				0xFF	/* 设备当班 */
#define DEV_POWERON				0xFF	/* 设备加电 */
#define DEV_HEALTH				0xFF	/* 设备健康 */
#define DEV_UPDATA				0xFF	/* 设备更新 */
#define DEV_INVALID				0x00	/* 设备不当班/不健康/断电状态 */

#define DEVID_FOG1				3	 /* GYRO1 */
#define DEVID_FOG2				4	 /* GYRO2 */
#define DEVID_FOG3				5	 /* GYRO3 */

/* ----------------------------------------------------------------------------------------- */
/* 设备状态结构体 */
typedef struct TAG_DEVICE_TABLE
{
	unint32 flgUpdata;		/* 是否允许自主更新 */
	unint32 devid;			/* 设备代号 */
	unint32 flgPower;		/* 设备加电状态, 0x00表示加电, 0xFF表示断电 */
	unint32 flgDuty;		/* 设备当班状态, 0x00表示当班, 0xFF表示不当班 */
	unint32 flgHealth;		/* 设备健康状态, 0x00表示健康, 0xFF表示不健康 */
	
	siint32 cntDuty;		/* 当班状态改变计数 */
	siint32 cntPower;		/* 加电状态改变计数 */
} SDeviceTable;

/* 设备总数(含无效占位设备) */
#define IEMS_DEVID_NUM			   (94)
/* 设备总数(含无效占位设备) */
#define GNC_DEVID_NUM			   (13)

extern SDeviceTable IemsDevTable[IEMS_DEVID_NUM];
extern SDeviceTable gncDevTable[GNC_DEVID_NUM];


typedef struct TAG_STS_DATA_RAW
{
	unint32 bComSuc;
	unint32 bValid;
	unint32 flagStatus;
	siint32 cntSynPulse;
	siint32 datation;
	unint32 quality;
	unint32 NumStarsIdentified;
	unint32 qRaw[4];
	unint32 wRaw[3];

	float64 q[4];
	float64 w[3];

	float64 time;

	unint08 tmBuff08[21];		/* */

	unint08 tmHk1Buff08[64];	/* */
	unint08 tmZtBuff08[128];		/* */
	unint08 tmHknBuff08[256];	/* */
} SStsDataRaw;

typedef struct TAG_STS_DATA_RAW_PARAM
{
	siint32 numStarValid;

} SStsDataRawParam;

/* 星敏PPS数据 */
typedef struct TAG_STS_PPS
{
	float64 timePps;			/* 上一个PPS发出的时刻 */
	float64 timePpsPr1;			/* 上上个PPS发出的时刻 */

	float64 dltPps;				/* 上一个PPS和当前时刻的时间差 */

	siint32 cntSynPulse;		   /* 同步脉冲数 */
	siint32 cntSynPulsePr1;		/* 上一次的测量时间 */
} SStsPps;

/* 加电时间判断 */
typedef struct TAG_POWER_JUDGE
{
	siint32 cntPowerOff;
	siint32 cntPowerOn;
	unint32 bPowerOnOk;
	unint32 powerPr1;

	siint32 cntSoftPowerOn;      /* 软电源状态加电计数器,通信故障诊断使能使用 */
	unint32 softPowerPr1;        /* 上周期软电源状态 */

	unint32 flgPower;            /* 选用的加电状态 */
	unint32 flgHardPower;        /* 硬加电状态 */
	unint32 flgSoftPower;        /* 软加电状态 */
	unint32 flgPowerSel;         /* 加电状态选择标志,FALSE32为选硬件，TRUE32为选软件，默认为FALSE32，选硬件 */
} SPowerJudge;

typedef struct TAG_POWER_JUDGE_PARAM
{
	siint32  numOffPeriod;
	siint32  numOnPeriod;
} SPowerJudgeParam;

/* 陀螺头原始数据参数 */
typedef struct TAG_GYRO_DATA_RAW_PARAM
{
	float64 cofWt0;			   /* 陀螺角速度增量当量 */
} SGyroDataRawParam;


/* 串口通信错误数据结构 */
typedef struct TAG_COM_ERROR
{
	siint32 cntLenRd;		 /* 连续读取长度错误计数 */		
	siint32 cntHead;		  /* 连续帧头错误计数 */
	siint32 cntLen;		   /* 连续长度错误计数(指的是协议中的长度信息) */
	siint32 cntCheck;		 /* 连续校验错误计数 */
	siint32 cntUpdata;		/* 连续数据更新错误计数 */

	siint32 totalLenRd;	   /* 累计读取长度错误计数 */  
	siint32 totalHead;		/* 累计帧头错误计数 */	
	siint32 totalLen;		 /* 累计长度错误计数 */	
	siint32 totalCheck;	   /* 累计校验错误计数 */	
	siint32 totalUpdata;	  /* 累计数据更新错误计数 */
} SComError;

extern SPowerJudgeParam mPowerJudgeStsParam;
extern SStsDataRawParam mStsDataRawParam[3];
extern SPowerJudgeParam mPowerJudgeDssXYParam;
extern SPowerJudgeParam mPowerJudgeFogParam;
extern SPowerJudgeParam mPowerJudgeImuGyroParam;
extern SGyroDataRawParam mImuGyroDataRawParam[3];


/* 硬件相关的结构体定义 */
typedef struct TAG_UART
{
	unint32 cntRead;			/* 读数据长度区 */
	unint08 buff08Read[256];	/* 读缓冲区 */
	
	unint32 cntWrite;			/* 写数据长度区 */
	unint08 buff08Write[256];	/* 写缓冲区 */
} SUart;

SUart mUartFog[NUM_FOG];

#endif
