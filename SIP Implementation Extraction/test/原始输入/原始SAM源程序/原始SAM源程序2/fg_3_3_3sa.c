
#include "fg_3_3_3sa.h"
#include "malloc.h"

unint32 Fg333sacntFrame;

/* 功能: fg_3_3_3sa取数命令打包 */
unint32 SendFg333saCmd(unint08 *pSendBuf)
{
	unint32 tmpLen;
	
    /* 打包取数指令 */
    pSendBuf[0] = 0xEB;
    pSendBuf[1] = 0x90;
	
	tmpLen = 2;
	
    return tmpLen;
}

/* 功能: fg_3_3_3sa协议校验 */
/* input: */
unint32 Fg333saCheck(const unint08 *pbuff, unint32 rdLen, unint32 *frm, unint32 *pFgRaw)
{
	unint32 bComSuc;
	unint08 chksum;
	SFg333saRaw *pRaw;
	
	pRaw = (SFg333saRaw *)pFgRaw;
	
	bComSuc = FALSE32;
	
	if(rdLen == 19)
	{
		pRaw->cntLenRd = 0;

		/* 帧计数是否更新 */
		if (pbuff[17] != (*frm))
		{
			pRaw->cntUpdata = 0;
			
			*frm = pbuff[17];
			
			/* 帧头为0xEB90 */
			if((pbuff[0] == 0xEB)&&(pbuff[1] == 0x90))
			{
				pRaw->cntHead = 0;
			
				/* 计算累加和 */
				chksum = CheckSumAdd08(&pbuff[0], 18);
			
				/* 累加和正确 */
				if(chksum == pbuff[18])
				{
					pRaw->cntCheck = 0;
					
					bComSuc = TRUE32;
				}
				else
				{
					/* 累加和不正确 */
					pRaw->cntCheck++;
					pRaw->totalCheck++;
				}
			}
			else
			{
				/* 帧头不正确 */
				pRaw->cntHead++;
				pRaw->totalHead++;
			}
		}
		else
		{
			pRaw->cntUpdata++;
			pRaw->totalUpdata++;
		}
	}
	else
	{
		/* 数据长度不对 */
		pRaw->cntLenRd++;
		pRaw->totalLenRd++;
	}

	return bComSuc;
}

/* 功能: fg_3_3_3sa协议解析 */
void Fg333saUnPack(unint32 *pFgRaw, const unint08 *pRecvbuf,float64 dtime)
{
	SFg333saRaw *pRaw;
	unint32 temp_var;

	pRaw = (SFg333saRaw *)pFgRaw;

	temp_var = UI32_MAKE(pRecvbuf[2], pRecvbuf[3], pRecvbuf[4], pRecvbuf[5]);
	pRaw->wt0 = ((float64)(siint32)temp_var) / 3.0e6 * DEG2RAD;

	pRaw->glwd1 = UI16_MAKE(pRecvbuf[6], pRecvbuf[7]);
	pRaw->glwd2 = UI16_MAKE(pRecvbuf[8], pRecvbuf[9]);
	pRaw->dlwd = UI16_MAKE(pRecvbuf[10], pRecvbuf[11]);

	pRaw->status = pRecvbuf[16];
	
	/* 陀螺计算角度增量 */
	pRaw->gf = pRaw->wt0 * dtime;

	return;
}


int main(){
    unint08 *pbuff = malloc(sizeof(unint08));
    unint32 rdLen = 2;
    unint32 *frm = malloc(sizeof(unint32));
    unint32 *pFgRaw = malloc(sizeof(unint32));
    Fg333saCheck(pbuff, rdLen, frm, pFgRaw);

    unint32 *pFgRaw_2 = malloc(sizeof(unint32));
    const unint08 *pRecvbuf = malloc(sizeof(unint08));
    float64 dtime = 1.0;
    Fg333saUnPack(pFgRaw_2, pRecvbuf, dtime);

}