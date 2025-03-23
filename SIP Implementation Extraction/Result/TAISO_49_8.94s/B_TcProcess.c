#include "B_TcProcess.h"
void B_TcProcessFun(void *p) 
{
    B_TcProcess *pIp = (B_TcProcess*)p;

	unint08 chksum;
	unint08 i;

	if ((pIp -> tcaData[0] == 0xE1) && (pIp -> tcaData[1] == 0x00))					/* ��ͷ��ȷ */
	{		
		{IPCALL(CheckCal,ipCheckCal_0,.len = 3,.pkv = &tcaData[0],.chksum = &chksum);}
	    if(pIp -> tcaData[3] == chksum)
	    {
	    	/* У�����ȷ */
	    	if(pIp -> tcaData[2] == 0)
	    	{
	    		TR32_FLGMODE_VALUE(SAM_DAMP) ;							/* �������᷽ʽ */
	    	}
	    	else if(pIp -> tcaData[2] == 1)
	    	{
	    		TR32_FLGMODE_VALUE(SAM_CRUISE) ;					    /* ��Ѳ��ģʽ */
	    	}
	    	else
	    	{
	    		TR32_FLGMODE_VALUE(NOCTRL) ;					    	/* ������ģʽ */
	    	}
	    }
	}

	return;
}