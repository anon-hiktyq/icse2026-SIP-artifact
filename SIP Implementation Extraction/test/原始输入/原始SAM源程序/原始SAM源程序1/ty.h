
/* --------基本数据类型-------- */
typedef unsigned char   unint08;
typedef signed   char   siint08;
typedef signed   int    siint16;
typedef unsigned int    unint16;
typedef signed   long   siint32;
typedef unsigned long   unint32;
typedef float           float32;


/* --------结构体定义-------- */
/* 基本数据类型之间转换 */
typedef union TAG_DATA_TYPE_CONVERT
{

    unint08 ui08[4];				 	/* 单精度数据转化为1个4字节整型数 */
    float32 flt32;
    unint32 ui32;

} UDTConvert;

/* 姿态结构 */
typedef struct TAG_ATTITUDE_PARA
{

	float32 	angle[3];			 	/* 三轴姿态角 */
	float32 	rate[3]; 			 	/* 三轴角速度 */

}SAttitude;

/* 敏感器输入结构 */
typedef struct TAG_DSS_DATA
{

	unint16 	SS1;
	unint16 	SS2;
	float32 	royaw;
	float32 	piyaw;

}SDSSData;

/* 陀螺数据 */
typedef struct TAG_DIGITAL_GYRO_DATA
{

    unint08		countPick[9];		 	/* 陀螺原始数据处理时,剔野计数器 */
    float32 	Gi[3];				 	/* 陀螺角度积分 */
    float32 	wa[9];				 	/* 陀螺角速度模拟 */
    float32 	wal[9];				 	/* 上周期陀螺角速度模拟量 */
 	unint08		JoinTotal;           	/* 参加定姿的陀螺个数 */
 	unint16 	gyroStatus0;		 	/* 陀螺状态旧 */
 	unint16 	gyroStatus1;		 	/* 陀螺状态新 */
    float32 	W[3];				 	/* 陀螺算出的角速度 */
    unint08		SignFlag[9] ; 		 	/* 参加定姿的陀螺序号 */
    unint08		StateFlag[9];        	/* 陀螺状态标志 */
	float32 	Rtemp[3][5];		 	/* 矩阵计算结果 */

} SGyroData;

/* 控制器输入结构 */
typedef struct TAG_CONTROLLERIN
{

    float32 	Up;						/* 输入参数 */
    float32 	Ud;						/* 输入参数 */
    float32 	fy;						/* 输出 */

}SController;

/* 控制器参数结构 */
typedef struct TAG_CONTROLLER_PARAM
{

    float32 	Kp;             		/* PD参数 */
    float32 	Kd;             		/* PD参数 */
    float32 	h1;             		/* 开坎值 */

} SControllerParam;

/* 伪速率调制器结构 */
typedef struct TAG_FALSE_RATE_MODULATOR
{

	float32 	u;						/* 输入信号,即控制器输出 */
	float32 	r;						/* 反馈信号 */
	unint08 	Yp;						/* 脉冲方向输出 */
	unint08 	Yn;						/* 脉冲方向输出 */

}SFratemodulator;

/* 14个10N推力器按2ms输出 */
typedef struct TAG_UPS_2MS
{

	unint16 flgABChoose;				/* 推力器分支选择标志 */
    unint08 wPulse;         			/* 推力器输出缓冲区,32个2ms中断时输出的10N脉冲字 */

} SThrDistribute;

/* 故障警报 */
typedef struct TAG_FAULT_WARNING
{
	unint08 CWsp;
	unint08 CWtf;

    unint08 Wsp;                        /* 太阳敏感器软件故障报警 */
    unint08 Wtf;                        /* 喷气频繁软件故障报警 */
    unint08 Wav;

    unint08 flgups;						/* UPS切换标志 */
    unint08 flgModeChange;				/* 模式切换标志 */

	unint16 countAV;
    unint16 countSPLost;				/* 太敏丢失计数器 */
    unint16 countSPSeen;				/* 太敏可见计数器 */
    unint16 countSPset;					/* 切换太敏计数器 */
    unint16 countUPSpc;					/* 第二次搜索切换UPS程控计数器 */

} SFWarning;

/* 软件中记忆的电源状态,1表示加电 0x800C  */
typedef union TAG_POWER_STATUS1
{
    unint16 ui16;

    struct TAG_POWER_STATUS_BIT1
    {

		unint16 FT_A_PS 	: 1;		/* FT主份电源状态 */
		unint16 FT_B_PS 	: 1;    	/* FT备份电源状态 */
		unint16 OBC_A_PS	: 1;    	/* OBC主份电源状态 */
		unint16 OBC_B_PS	: 1;    	/* OBC备份电源状态 */
		unint16 OBC_A_DUTY  : 1;     	/* OBC主份当班 */
		unint16 OBC_B_DUTY  : 1;     	/* OBC备份当班 */
		unint16 SADA_A_PS 	: 1;    	/*  */
		unint16 SADA_B_PS 	: 1;    	/*  */
		unint16 BAKH8		: 8;

    }Bit;

}UPowerWord1;

/*  0xC000 */
typedef union TAG_POWER_STATUS2
{
	unint16 ui16 ;

	struct TAG_POWER_STATUS_BIT2
	{

		unint16 SSE_A_PS 	: 1;		/* 开主关备 */
		unint16 SSE_B_PS 	: 1;    	/* 开备关主 */
		unint16 FOG1_PS		: 1;    	/* FOG1 */
		unint16 FOG2_PS		: 1;    	/* FOG2 */
		unint16 FOG3_PS 	: 1;    	/* FOG3 */
		unint16 GYRO1_PS  	: 1;    	/* GYRO4 */
		unint16 GYRO2_PS 	: 1;    	/* GYRO5 */
		unint16 GYRO3_PS 	: 1;    	/* GYRO6 */
	    unint16 BAKH8		: 8;
	}Bit;

}UPowerWord2;

/* 软件中记忆的电源状态,1表示加电 0xE000  */
typedef union TAG_POWER_STATUS3
{
    unint16 ui16;

    struct TAG_POWER_STATUS_BIT3
    {

		unint16 GYRO4_PS 	: 1;		/* FT主份电源状态 */
		unint16 GYRO5_PS 	: 1;    	/* FT备份电源状态 */
		unint16 GYRO6_PS	: 1;    	/* OBC主份电源状态 */
		unint16 UPS_A_PS 	: 1;    	/*  */
		unint16 UPS_B_PS 	: 1;    	/*  */
		unint16 SPSee		: 1;		/* SP可见标志 */
		unint16 BAK		    : 2;
		unint16 BAKH8	    : 8;
    }Bit;

}UPowerWord3;

/*  0x8000 */
typedef union TAG_INPUT_IO1_STATUS
{
	unint16 ui16;

	struct TAG_INPUT_IO1_STATUS_BIT
	{

		unint16 SSE_A 		: 1;		/* 开主份SSE */
		unint16 SSE_B 		: 1;    	/* 开备份SSE */
		unint16 FOG1   		: 1;    	/* FOG1 */
		unint16 FOG2   		: 1;    	/* FOG2 */
		unint16 FOG3   		: 1;    	/* FOG3 */
		unint16 GYRO4  		: 1;    	/* GYRO4 */
		unint16 GYRO5	 	: 1;    	/* GYRO5 */
		unint16 GYRO6 		: 1;    	/* GYRO6 */
		unint16 BAKH8	    : 8;
	}Bit;

}UInpIO1;

/* UInpIO2 0x8004 */
typedef union TAG_INPUT_IO2
{
	unint16 ui16;

	struct TAG_INPUT_IO2_BIT
	{
		unint16 GYRO_1		:1;			/* GYRO_1 */
		unint16 GYRO_2		:1;			/* GYRO_2 */
		unint16 GYRO_3		:1;			/* GYRO_3 */
		unint16 SADA		:1;			/* SADA复位 */
		unint16 LV14		:1;			/* 开UPS自锁阀1、4和母线A */
		unint16 LV23		:1;			/* 开UPS自锁阀2、3和母线B */
		unint16 BUS_AB_G	:1;			/* 关UPS电源母线A、B */
		unint16 LV1234_G	:1;			/* 关UPS自锁阀1、4和2、3 */
		unint16 BAKH8	    : 8;
	}Bit;

}UInpIO2;

/* UInpIO2UPS 0x8008 */
typedef union TAG_INPUT_IO3_UPS
{
	unint16 ui16;

	struct TAG_INPUT_IO3_UPS_BIT
	{

		unint16 GAE_135		: 1;	 	/* 开陀螺1、3、5马达 */
		unint16 GAE_246 	: 1;	 	/* 开陀螺2、4、6马达 */
		unint16 PULSE_2AB 	: 1;	 	/* 2AB控制脉冲 */
		unint16 PULSE_3AB 	: 1;	 	/* 3AB控制脉冲 */
		unint16 PULSE_4AB 	: 1;	 	/* 4AB控制脉冲 */
		unint16 PULSE_5AB 	: 1;	 	/* 5AB控制脉冲 */
		unint16 PULSE_6AB 	: 1;	 	/* 6AB控制脉冲 */
		unint16 PULSE_7AB 	: 1;	 	/* 7AB控制脉冲 */
		unint16 BAKH8     	: 8;	 	/* D8-D15      */

	}Bit;
}UInpIO3;

typedef union TAG_INPUT_HEALTH_HI
{
	unint16 ui16;

	struct TAG_INPUT_HEALTH_BIT_HI
	{
		unsigned J_STS_1   	:1;			/* D16 */
		unsigned J_STS_2   	:1;			/* D17 */
		unsigned J_STS_3   	:1;			/* D18 */
		unsigned J_GA_1	  	:1;			/* D19 */
		unsigned J_GA_2  	:1;			/* D20 */
		unsigned J_GA_3 	:1;			/* D21 */
		unsigned J_GA_4 	:1;			/* D22 */
		unsigned J_GA_5 	:1;			/* D23 */
		unsigned J_GA_6  	:1;			/* D24 */
		unsigned J_GA_7  	:1;			/* D25 */
		unsigned J_GA_8  	:1;			/* D26 */
		unsigned J_GA_9  	:1;			/* D27 */
		unsigned BAKB13  	:1;			/* D28 */
		unsigned J_OBC  	:1;			/* D29 */
		unsigned BAKBH  	:2;			/* D30-31 */

	}Bit;
}UHealthwordHi;

typedef union TAG_INPUT_HEALTH_LO
{
	unint16 ui16;

	struct TAG_INPUT_HEALTH_BIT_LO
	{
		unsigned J_UPS_A	:1;			/* D0  */
		unsigned J_UPS_B    :1;			/* D1  */
		unsigned J_SADAE_A	:1;			/* D2  */
		unsigned J_SADAE_B	:1;			/* D3  */
		unsigned J_MW1		:1;			/* D4  */
		unsigned J_MW2		:1; 		/* D5  */
		unsigned J_MW3		:1; 		/* D6  */
		unsigned J_MW4		:1;			/* D7  */
		unsigned J_MW5		:1;			/* D8  */
		unsigned J_MW6		:1;			/* D9  */
		unsigned J_MW7	    :1;			/* D10 */
		unsigned J_MW8		:1;			/* D11 */
		unsigned J_SSE_A   	:1;			/* D12 */
		unsigned J_SSE_B   	:1;			/* D13 */
		unsigned J_FT_A    	:1;			/* D14 */
		unsigned J_FT_B    	:1;			/* D15 */

	}Bit;
}UHealthwordLo;









