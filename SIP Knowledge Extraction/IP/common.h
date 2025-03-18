#if !defined(__COMMON_H__)
#define __COMMON_H__



typedef void            (*Fun)(void *);

#define IPCALL(IP)		(IP.fun(&IP))

#define IPCREATE(IpName, InstName, ...) IpName InstName = {.fun = IpName ## Fun, __VA_ARGS__};

#define TRUE            			0xEB

#define FALSE           			0x00




#define SAM_DAMP            		0x00	/* SAM�������᷽ʽ */

#define FST_FLGMODE					((volatile unint08 *)0x7D00)

#define FST_BIAS_WXRO       		((volatile float32 *)0x7D18)

#define FST_BIAS_WYPI       		((volatile float32 *)0x7D1C)

#define SND_FLGMODE					((volatile unint08 *)0x7E54)

#define SND_BIAS_WXRO       		((volatile float32 *)0x7E6C)

#define SND_BIAS_WYPI       		((volatile float32 *)0x7E70)

#define TRD_FLGMODE					((volatile unint08 *)0x7FA8)

#define TRD_BIAS_WXRO       		((volatile float32 *)0x7FC0)

#define TRD_BIAS_WYPI       		((volatile float32 *)0x7FC4)

#define TR32_FLGMODE_VALUE(x)		TR32_VALUE(FST_FLGMODE, SND_FLGMODE, TRD_FLGMODE, (x))

#define TR32_BIAS_WXRO_VALUE(x)		TR32_VALUE(FST_BIAS_WXRO, SND_BIAS_WXRO, TRD_BIAS_WXRO, (x))

#define TR32_BIAS_WYPI_VALUE(x)		TR32_VALUE(FST_BIAS_WYPI, SND_BIAS_WYPI, TRD_BIAS_WYPI, (x))

#define TR32_VALUE(pA,pB,pC,nval)   {*(pA) = (nval);    *(pB) = (nval);    *(pC) = (nval);}

typedef unsigned char   unint08;

typedef unsigned int    unint16;

typedef unsigned long   unint32;

typedef float           float32;

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
	float32 	Rtemp[3][5];		 	/* ��������� */
	unint32		stateFlag[9];			/* ���ݼӵ�״̬ */
	
} SGyroData;

typedef struct TAG_FALSE_RATE_MODULATOR
{
	
	float32 	u;						/* �����ź�,����������� */
	float32 	r;						/* �����ź� */
	unint08 	Yp;						/* ���巽����� */
	unint08 	Yn;						/* ���巽����� */
	                            	
}SFratemodulator;

typedef struct TAG_UPS_2MS
{	
	unint16 flgABChoose;				/* ��������֧ѡ���־ */
    unint08 wPulse;         			/* ���������������,32��2ms�ж�ʱ�����10N������ */
	unint08 stateFlag[2];				/* �������ӵ�״̬ stateFlag[0]���ݣ�stateFlag[1]���ݣ� ȡֵΪ1ʱ�ӵ磬0ʱ�ϵ�*/
    
} SThrDistribute;

typedef struct TAG_FAULT_WARNING
{
	unint08 CWsp;
	unint08 CWtf;
	
    unint08 Wsp;                        /* ̫���������������ϱ��� */	
    unint08 Wtf;                        /* ����Ƶ���������ϱ��� */
    unint08 Wav;
    
    unint08 flgups;						/* UPS�л���־ */
    unint08 flgModeChange;				/* ģʽ�л���־ */
    
	unint16 countAV;
    unint16 countSPLost;				/* ̫����ʧ������ */
    unint16 countSPSeen;				/* ̫���ɼ������� */
    unint16 countSPset;					/* �л�̫�������� */
    unint16 countUPSpc;					/* �ڶ��������л�UPS�̿ؼ����� */
     
} SFWarning;

#define ADDR_WRITE(addr, value)     {(*((volatile unint32 *)(addr))) = (value);}

#define ADDR_READ(addr)             (*((volatile unint32 *)(addr)))

#define SAM_CRUISE          		0x33	/* SAMѲ����ʽ */

#define NOCTRL						0x44	/* ���� */

typedef signed   int    siint16;

#define DIVIATION_TO_FLOAT_FOG(x)   DiviationToFloat((x), 0xFFF, 0x800, 9.765625e-4f)      /*    1/1024�� */

#define DIVIATION_TO_FLOAT_DSS(x)	DiviationToFloat((x), 0xFFF, 0x800, 2.44140625e-3f)  /*  5/2048 -5~5�� */

typedef struct TAG_DSS_DATA
{	
	unint32     stateFlag_A;			/* ���ݼӵ� */
	unint32     stateFlag_B;			/* ���ݼӵ� */
	float32 	royaw;
	float32 	piyaw;
    unint32     flgSP;					/* ̫���ɼ���־ */
}SDSSData;

#define TBS_A               		0x00     /* ѡ��A��֧ */

#define TBS_B               		0x33     /* ѡ��B��֧ */

#define TBS_AB              		0xCC     /* ѡ��AB��֧ */

#define ABS(a)                  	(((a) > 0) ? (a) : -(a))

#define TRUE32                     0x90  /* ���ز����涨�� */

#define FALSE32                    0x00  /* ���ز����ٶ��� */

#define FLT32_ZERO                 1.0E-6

typedef signed   char   siint08;

#define MIN(a, b)                   (((a) > (b)) ? (b) : (a))

#define TR32_FLGMODE()				Tr32Uint08(FST_FLGMODE, SND_FLGMODE, TRD_FLGMODE)

typedef struct TAG_ATTITUDE_PARA     	
{                                    	
	                                 	
	float32 	angle[3];			 	/* ������̬�� */
	float32 	rate[3]; 			 	/* ������ٶ� */
	                                 	
}SAttitude;

#define SAM_PITCH           		0x11	/* SAM����������ʽ */

#define SAM_ROLL            		0x22	/* SAM����������ʽ */

typedef struct TAG_CONTROLLERIN
{
    
    float32 	Up;						/* ������� */
    float32 	Ud;						/* ������� */
    float32 	fy;						/* ��� */
    
}SController;

typedef union TAG_DATA_TYPE_CONVERT
{
      
    unint08 ui08[4];				 	/* ����������ת��Ϊ1��4�ֽ������� */  
    float32 flt32;                   	
    unint32 ui32;                    	
                                     	
} UDTConvert;

#define TR32_BIAS_WXRO()			Tr32Float(FST_BIAS_WXRO, SND_BIAS_WXRO, TRD_BIAS_WXRO)

#define TR32_BIAS_WYPI()			Tr32Float(FST_BIAS_WYPI, SND_BIAS_WYPI, TRD_BIAS_WYPI)

typedef struct TAG_CONTROLLER_PARAM
{
    
    float32 	Kp;             		/* PD���� */
    float32 	Kd;             		/* PD���� */
    float32 	h1;             		/* ����ֵ */
    
} SControllerParam;

#define MASK_LO08                       0x000000FFu     /* 32λ�еĵ�8λ */

#define UI32_HIHI8(ui32)                (((ui32) >> 24) & MASK_LO08)

#define UI32_HILO8(ui32)                (((ui32) >> 16) & MASK_LO08)

#define UI32_LOHI8(ui32)                (((ui32) >>  8) & MASK_LO08)

#define UI32_LOLO8(ui32)                (((ui32)      ) & MASK_LO08)

#define UI16_HI8(ui16)                  (((ui16) >>  8) & MASK_LO08)

#define UI16_LO8(ui16)                  (((ui16)      ) & MASK_LO08)



#endif // __COMMON_H__