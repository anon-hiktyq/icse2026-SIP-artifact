#include "gnc_input.h"
#include "config.h"
#include "fg_3_3_3sa.h"
#include "malloc.h"

SPowerJudge mPowerJudgeSts[STS_NUM];
SStsDataRaw mStsDataRaw[STS_NUM];
SStsPps mStsPps[STS_NUM];
SComError mComErrorSts[STS_NUM];
SPowerJudge mPowerJudgeFog[NUM_FOG];
SFg333saRaw mFogDataRaw[NUM_FOG];
SPowerJudge mPowerJudgeImuGyro[NUM_IMU_GYRO];
SPowerJudge mPowerJudgeDssXY[DSS_XY_NUM];

void PowerOnJudge(SPowerJudge *ptrPowerJudge,SPowerJudgeParam *ptrPowerJudgeParam);


/* 输入数据处理 */
void InputData(void)
{
	siint32 si;
	
	/* 光纤陀螺数据处理 */
	for(si=0;si<NUM_FOG;si++)
	{
		/* 电源状态选择（软标志还是硬标志） */
		if (mPowerJudgeFog[si].flgPowerSel == TRUE32)
		{
			gncDevTable[DEVID_FOG1+si].flgPower = mPowerJudgeFog[si].flgSoftPower;	
		}
		mPowerJudgeFog[si].flgPower = gncDevTable[DEVID_FOG1+si].flgPower;
		
		/* 光纤陀螺加电处理 */
		PowerOnJudge(&mPowerJudgeFog[si],&mPowerJudgeFogParam);
		
		if(DEV_IS_POWERON(gncDevTable[DEVID_FOG1+si]))
		{
			mFogDataRaw[si].bComSuc = Fg333saCheck(&mUartFog[si].buff08Read[0], mUartFog[si].cntRead, &mFogDataRaw[si].cntFrame,(unint32 *)(&mFogDataRaw[si]));
			
			if (mFogDataRaw[si].bComSuc == TRUE32)
			{
				Fg333saUnPack((unint32 *)(&mFogDataRaw[si]), &mUartFog[si].buff08Read[0],TS);
			}
		}
		else
		{
			mFogDataRaw[si].bComSuc = FALSE32;

			/* 新增需求，未加电则清零，避免陀螺积分一直累计 */
			mFogDataRaw[si].gf = 0.0;
		}
	}
	return;
}

/* 加电状态判断 */
void PowerOnJudge(SPowerJudge *ptrPowerJudge,SPowerJudgeParam *ptrPowerJudgeParam)
{
	unint32 powerState;

	powerState = ptrPowerJudge->flgPower;

	/* 本周期电源状态为断电 */
	if(powerState == DEV_INVALID)
	{
		if(ptrPowerJudge->cntPowerOff < ptrPowerJudgeParam->numOffPeriod)
		{
			ptrPowerJudge->cntPowerOff++;
		}
		else
		{
			/* 已断电 */
			ptrPowerJudge->cntPowerOn = 0;
			ptrPowerJudge->powerPr1 = DEV_INVALID;
			ptrPowerJudge->bPowerOnOk = FALSE32;
		}
	}
	else if((ptrPowerJudge->powerPr1 == DEV_INVALID) && (powerState == DEV_POWERON))  /* 电源状态由断电变加电 */
	{
		ptrPowerJudge->cntPowerOn++;

		if(ptrPowerJudge->cntPowerOn > ptrPowerJudgeParam->numOnPeriod)	/* >32s */
		{
			ptrPowerJudge->cntPowerOff = 0;

			/* 认为已加电大于30s */
			ptrPowerJudge->bPowerOnOk = TRUE32;

		}
		else
		{
			/* 加电不足30s,延续上一周期的电源状态 */
			powerState = DEV_INVALID;
		}
	}
	else
	{
		/* 电源状态没有发生变化 */
		NULL_STATEMENT();
	}

	/* 保存本周期电源状态 */
	ptrPowerJudge->powerPr1 = powerState;

	return;
}

int main(){
    SPowerJudge *ptrPowerJudge = malloc(sizeof(SPowerJudge));
    SPowerJudgeParam *ptrPowerJudgeParam = malloc(sizeof(SPowerJudgeParam));
    PowerOnJudge(ptrPowerJudge, ptrPowerJudgeParam);
}
