#include "gnc_input.h"
#include "config.h"

SPowerJudgeParam mPowerJudgeStsParam = 
{
	1,			/* siint32  numOffPeriod */
	160,		/* siint32  numOnPeriod */
};

SStsDataRawParam mStsDataRawParam[STS_NUM] =
{
	{4},	/* siint32 numStarValid */
	{4},	/* siint32 numStarValid */
	{4},	/* siint32 numStarValid */
};

SPowerJudgeParam mPowerJudgeDssXYParam =
{
	1,			/* siint32  numOffPeriod */
	32,			/* siint32  numOnPeriod */
};

SPowerJudgeParam mPowerJudgeFogParam =
{
	1,			/* siint32  numOffPeriod */
	80,		    /* siint32  numOnPeriod */
};

SPowerJudgeParam mPowerJudgeImuGyroParam =
{
	1,			/* siint32  numOffPeriod */
	80,			/* siint32  numOnPeriod */
};

SGyroDataRawParam mImuGyroDataRawParam[NUM_IMU_GYRO] =
{
	/* float64 cofWt0;			   陀螺角速度增量当量 */
	9.972296e4,9.869023e4,9.838731e4,
};
