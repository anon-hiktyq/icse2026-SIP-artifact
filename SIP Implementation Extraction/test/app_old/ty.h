
/* --------������������-------- */
typedef unsigned char   unint08;
typedef signed   char   siint08;
typedef signed   int    siint16;
typedef unsigned int    unint16;
typedef signed   long   siint32;
typedef unsigned long   unint32;
typedef float           float32;


/* --------�ṹ�嶨��-------- */
/* ������������֮��ת�� */
typedef union TAG_DATA_TYPE_CONVERT
{

    unint08 ui08[4];				 	/* ����������ת��Ϊ1��4�ֽ������� */
    float32 flt32;
    unint32 ui32;

} UDTConvert;

/* ��̬�ṹ */
typedef struct TAG_ATTITUDE_PARA
{

	float32 	angle[3];			 	/* ������̬�� */
	float32 	rate[3]; 			 	/* ������ٶ� */

}SAttitude;

/* ����������ṹ */
typedef struct TAG_DSS_DATA
{

	unint16 	SS1;
	unint16 	SS2;
	float32 	royaw;
	float32 	piyaw;

}SDSSData;

/* �������� */
typedef struct TAG_DIGITAL_GYRO_DATA
{

    unint08		countPick[9];		 	/* ����ԭʼ���ݴ���ʱ,��Ұ������ */
    float32 	Gi[3];				 	/* ���ݽǶȻ��� */
    float32 	wa[9];				 	/* ���ݽ��ٶ�ģ�� */
    float32 	wal[9];				 	/* ���������ݽ��ٶ�ģ���� */
 	unint08		JoinTotal;           	/* �μӶ��˵����ݸ��� */
 	unint16 	gyroStatus0;		 	/* ����״̬�� */
 	unint16 	gyroStatus1;		 	/* ����״̬�� */
    float32 	W[3];				 	/* ��������Ľ��ٶ� */
    unint08		SignFlag[9] ; 		 	/* �μӶ��˵�������� */
    unint08		StateFlag[9];        	/* ����״̬��־ */
	float32 	Rtemp[3][5];		 	/* ��������� */

} SGyroData;

/* ����������ṹ */
typedef struct TAG_CONTROLLERIN
{

    float32 	Up;						/* ������� */
    float32 	Ud;						/* ������� */
    float32 	fy;						/* ��� */

}SController;

/* �����������ṹ */
typedef struct TAG_CONTROLLER_PARAM
{

    float32 	Kp;             		/* PD���� */
    float32 	Kd;             		/* PD���� */
    float32 	h1;             		/* ����ֵ */

} SControllerParam;

/* α���ʵ������ṹ */
typedef struct TAG_FALSE_RATE_MODULATOR
{

	float32 	u;						/* �����ź�,����������� */
	float32 	r;						/* �����ź� */
	unint08 	Yp;						/* ���巽����� */
	unint08 	Yn;						/* ���巽����� */

}SFratemodulator;

/* 14��10N��������2ms��� */
typedef struct TAG_UPS_2MS
{

	unint16 flgABChoose;				/* ��������֧ѡ���־ */
    unint08 wPulse;         			/* ���������������,32��2ms�ж�ʱ�����10N������ */

} SThrDistribute;

/* ���Ͼ��� */
typedef struct TAG_FAULT_WARNING
{
	unint08 CWsp;
	unint08 CWtf;

    unint08 Wsp;                        /* ̫��������������ϱ��� */
    unint08 Wtf;                        /* ����Ƶ��������ϱ��� */
    unint08 Wav;

    unint08 flgups;						/* UPS�л���־ */
    unint08 flgModeChange;				/* ģʽ�л���־ */

	unint16 countAV;
    unint16 countSPLost;				/* ̫����ʧ������ */
    unint16 countSPSeen;				/* ̫���ɼ������� */
    unint16 countSPset;					/* �л�̫�������� */
    unint16 countUPSpc;					/* �ڶ��������л�UPS�̿ؼ����� */

} SFWarning;

/* ����м���ĵ�Դ״̬,1��ʾ�ӵ� 0x800C  */
typedef union TAG_POWER_STATUS1
{
    unint16 ui16;

    struct TAG_POWER_STATUS_BIT1
    {

		unint16 FT_A_PS 	: 1;		/* FT���ݵ�Դ״̬ */
		unint16 FT_B_PS 	: 1;    	/* FT���ݵ�Դ״̬ */
		unint16 OBC_A_PS	: 1;    	/* OBC���ݵ�Դ״̬ */
		unint16 OBC_B_PS	: 1;    	/* OBC���ݵ�Դ״̬ */
		unint16 OBC_A_DUTY  : 1;     	/* OBC���ݵ��� */
		unint16 OBC_B_DUTY  : 1;     	/* OBC���ݵ��� */
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

		unint16 SSE_A_PS 	: 1;		/* �����ر� */
		unint16 SSE_B_PS 	: 1;    	/* �������� */
		unint16 FOG1_PS		: 1;    	/* FOG1 */
		unint16 FOG2_PS		: 1;    	/* FOG2 */
		unint16 FOG3_PS 	: 1;    	/* FOG3 */
		unint16 GYRO1_PS  	: 1;    	/* GYRO4 */
		unint16 GYRO2_PS 	: 1;    	/* GYRO5 */
		unint16 GYRO3_PS 	: 1;    	/* GYRO6 */
	    unint16 BAKH8		: 8;
	}Bit;

}UPowerWord2;

/* ����м���ĵ�Դ״̬,1��ʾ�ӵ� 0xE000  */
typedef union TAG_POWER_STATUS3
{
    unint16 ui16;

    struct TAG_POWER_STATUS_BIT3
    {

		unint16 GYRO4_PS 	: 1;		/* FT���ݵ�Դ״̬ */
		unint16 GYRO5_PS 	: 1;    	/* FT���ݵ�Դ״̬ */
		unint16 GYRO6_PS	: 1;    	/* OBC���ݵ�Դ״̬ */
		unint16 UPS_A_PS 	: 1;    	/*  */
		unint16 UPS_B_PS 	: 1;    	/*  */
		unint16 SPSee		: 1;		/* SP�ɼ���־ */
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

		unint16 SSE_A 		: 1;		/* ������SSE */
		unint16 SSE_B 		: 1;    	/* ������SSE */
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
		unint16 SADA		:1;			/* SADA��λ */
		unint16 LV14		:1;			/* ��UPS������1��4��ĸ��A */
		unint16 LV23		:1;			/* ��UPS������2��3��ĸ��B */
		unint16 BUS_AB_G	:1;			/* ��UPS��Դĸ��A��B */
		unint16 LV1234_G	:1;			/* ��UPS������1��4��2��3 */
		unint16 BAKH8	    : 8;
	}Bit;

}UInpIO2;

/* UInpIO2UPS 0x8008 */
typedef union TAG_INPUT_IO3_UPS
{
	unint16 ui16;

	struct TAG_INPUT_IO3_UPS_BIT
	{

		unint16 GAE_135		: 1;	 	/* ������1��3��5��� */
		unint16 GAE_246 	: 1;	 	/* ������2��4��6��� */
		unint16 PULSE_2AB 	: 1;	 	/* 2AB�������� */
		unint16 PULSE_3AB 	: 1;	 	/* 3AB�������� */
		unint16 PULSE_4AB 	: 1;	 	/* 4AB�������� */
		unint16 PULSE_5AB 	: 1;	 	/* 5AB�������� */
		unint16 PULSE_6AB 	: 1;	 	/* 6AB�������� */
		unint16 PULSE_7AB 	: 1;	 	/* 7AB�������� */
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









