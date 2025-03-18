
#define    __DEBUG__				0
/* --------ģʽ�ֶ���-------- */

#define TRUE            			0xEB
#define FALSE           			0x00

#ifndef  TRUE32
#define  TRUE32                     0x90  /* ���ز����涨�� */
#endif
#ifndef  FALSE32
#define  FALSE32                    0x00  /* ���ز����ٶ��� */
#endif
#define  FLT32_ZERO                 1.0E-6

#define SAM_DAMP            		0x00	/* SAM�������᷽ʽ */
#define SAM_PITCH           		0x11	/* SAM����������ʽ */
#define SAM_ROLL            		0x22	/* SAM����������ʽ */
#define SAM_CRUISE          		0x33	/* SAMѲ����ʽ */
#define NOCTRL						0x44	/* ���� */



/* -------- ������AB��֧ѡ�� -------- */
#define TBS_A               		0x00     /* ѡ��A��֧ */
#define TBS_B               		0x33     /* ѡ��B��֧ */
#define TBS_AB              		0xCC     /* ѡ��AB��֧ */

/* --------��ȡ����������-------- */
#define FST_FLGMODE					((volatile unint08  *)0x7D00)
#define FST_BIAS_WXRO       		((volatile float32  *)0x7D18)
#define FST_BIAS_WYPI       		((volatile float32  *)0x7D1C)
#define FST_FT_HEALTHWORD      	    ((volatile unint32  *)0x7D24)

#define SND_FLGMODE					((volatile unint08  *)0x7E54)
#define SND_BIAS_WXRO       		((volatile float32  *)0x7E6C)
#define SND_BIAS_WYPI       		((volatile float32  *)0x7E70)
#define SND_FT_HEALTHWORD       	((volatile unint32  *)0x7E78)


#define TRD_FLGMODE					((volatile unint08  *)0x7FA8)
#define TRD_BIAS_WXRO       		((volatile float32  *)0x7FC0)
#define TRD_BIAS_WYPI       		((volatile float32  *)0x7FC4)
#define TRD_FT_HEALTHWORD       	((volatile unint32  *)0x7FCC)


#define TR32_FLGMODE()				Tr32Uint08(FST_FLGMODE, SND_FLGMODE, TRD_FLGMODE)
#define TR32_BIAS_WXRO()			Tr32Float(FST_BIAS_WXRO, SND_BIAS_WXRO, TRD_BIAS_WXRO)
#define TR32_BIAS_WYPI()			Tr32Float(FST_BIAS_WYPI, SND_BIAS_WYPI, TRD_BIAS_WYPI)
#define TR32_FT_HEALTHWORD()		Tr32Uint(FST_FT_HEALTHWORD, SND_FT_HEALTHWORD, TRD_FT_HEALTHWORD)

#define TR32_FLGMODE_VALUE(x)		TR32_VALUE(FST_FLGMODE, SND_FLGMODE, TRD_FLGMODE, (x))
#define TR32_BIAS_WXRO_VALUE(x)		TR32_VALUE(FST_BIAS_WXRO, SND_BIAS_WXRO, TRD_BIAS_WXRO, (x))
#define TR32_BIAS_WYPI_VALUE(x)		TR32_VALUE(FST_BIAS_WYPI, SND_BIAS_WYPI, TRD_BIAS_WYPI, (x))

#define TR16_VALUE(pA,pB,pC,nval)   {*(pA) = (nval);    *(pB) = (nval);    *(pC) = (nval);}
#define TR32_VALUE(pA,pB,pC,nval)   {*(pA) = (nval);    *(pB) = (nval);    *(pC) = (nval);}

#define WR_FST_FT_HEALTHWORD(x)    {*(FST_FT_HEALTHWORD) = (x);}
#define WR_SND_FT_HEALTHWORD(x)    {*(SND_FT_HEALTHWORD) = (x);}
#define WR_TRD_FT_HEALTHWORD(x)    {*(TRD_FT_HEALTHWORD) = (x);}

/* -------- �����ȸ�������ƫ�ƶ�������֮��ת������ -------- */
/* ̫����������������ת�� */
#define DIVIATION_TO_FLOAT_DSS(x)	DiviationToFloat((x), 0xFFF, 0x800, 2.44140625e-3f)  /*  5/2048 -5~5�� */
#define DIVIATION_TO_FLOAT_GYRO(x)  DiviationToFloat((x), 0xFFF, 0x800, 1.62760417e-3f)    /*  5/3072 -2.5~2.5��/S  */
#define DIVIATION_TO_FLOAT_FOG(x)   DiviationToFloat((x), 0xFFF, 0x800, 9.765625e-4f)      /*    1/1024�� */

#define ABS(a)                  	(((a) > 0) ? (a) : -(a))
#define MIN(a, b)                   (((a) > (b)) ? (b) : (a))
/* RAM��ַ��Ч���ж� */
#define RAM_VALIDATE(addr)      ((0x0  <= (addr)) && ((addr) <= 0x7FFF))




