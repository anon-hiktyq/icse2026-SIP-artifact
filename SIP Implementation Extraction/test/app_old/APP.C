#include "ec.h"

/* --------接口变量定义-------- */
unint08 flgSP ;

/* 功能： 应用软件主函数 */
void main1(void)
{
	AppInit1() ;									 			/* 初始化 */

	do														/* 控制周期循环160ms */
	{

		Input() ;									     /* 读入输入数据并转换  */

	    Inputproceed() ;								/* 包含：1 陀螺数据处理 2 姿态角和角速度赋值  */

		ModeControl() ;									/* 模式处理 */

		LimitControllerInput() ;						/* 在进入控制器运算之前，需要计算控制量并进行限幅处理 */

		ThreeAxisController() ;							/* 控制器模块 */

		Pulse_Out() ;									/* 脉冲输出统一处理 */

	} while(1) ;

}

/* 功能：应用软件初始化 */
void AppInit1(void)
{

	mGyroData.gyroStatus0 = 0 ;								/* 陀螺状态（旧） */
	mGyroData.gyroStatus1 = 0 ;								/* 陀螺状态（现） */

	/* 计数器初始化 */
	countPublic = 0 ;
	countMode = 0 ;											/* 控制周期计数 */

	/* 三取二分区初始化 */
	TR32_FLGMODE_VALUE(SAM_DAMP) ;							/* 默认速率阻尼方式 */
	TR32_BIAS_WXRO_VALUE(0.0f) ;							/* 角速度偏置量清零 */
	TR32_BIAS_WYPI_VALUE(0.0f) ;							/* 角速度偏置量清零 */

	mThrDistribute.wPulse = 0x0 ;	                        /* 将12个10N推力器对应变量输出清零 */

	/* 伪速率状态量清零 */
	mModulator[0].r = 0.0f ;
	mModulator[1].r = 0.0f ;
	mModulator[2].r = 0.0f ;

	flgGryoCalc = FALSE ;                                   /* 初始化清陀螺计算标志 */

	return ;
}



/* 功能：EC模式控制 */
void ModeControl(void)
{
	unint08 flgModetmp1 ;

	flgModetmp1 = TR32_FLGMODE() ;						    /* 三区读出方式字 */

    countMode++ ;											/* 控制周期计数累加 */

    if (flgModetmp1 == SAM_DAMP)							/* SAM子模式转换控制 */
    {
        SAMSubModeDamp() ;								    /* SAM速率阻尼方式 */
    }
    else if (flgModetmp1 == SAM_PITCH)
    {
        SAMSubModePitch() ;									/* SAM俯仰搜索方式 */
    }
    else if (flgModetmp1 == SAM_ROLL)
    {
        SAMSubModeRoll() ;									/* SAM滚动搜索方式 */
    }
    else if (flgModetmp1 == SAM_CRUISE)   					/* SAM巡航方式 */
    {
        SAMSubModeCruise() ;								/* SAM巡航方式 */
    }
    else
    {
    	TR32_FLGMODE_VALUE(SAM_DAMP) ;			            /* R534 若方式字不为规定的4种方式，则默认进入速率阻尼方式 */
    }

	return ;
}

/* 功能：速率阻尼 */
void SAMSubModeDamp(void)
{
    float32 fabsmax ;										/* 临时：绝对值最大 */

    fabsmax = TripleFabsMax( mAttitude.rate[0], mAttitude.rate[1], mAttitude.rate[2] ) ;/* 求三轴姿态角速度最大值 */

    if ( fabsmax < 0.15f )		 							/* 三轴姿态角速度均小于0.15度/秒 */
    {
        countPublic++ ;										/* 方式计数器 */
    }

    /* 若700Ts角速度都小于0.07度/s 或 速率阻尼持续时间大于128秒时,置俯仰角速度偏置为-0.5度/s, 转入俯仰搜索 */
    if (( countPublic > 280 ) || ( countMode > 800 ))
    {
        TR32_FLGMODE_VALUE(SAM_PITCH) ;						/* 转入俯仰搜索方式 */
        TR32_BIAS_WYPI_VALUE(-0.5f) ;						/* 俯仰角偏置0.5度 */

        countMode = 0 ;									    /* 清控制周期计数器 */
        countPublic = 0 ;									/* 方式计数器 */
    }

    return ;
}

/* 功能：俯仰搜索 */
void SAMSubModePitch(void)
{
    float32 pirawtmp  ;

    if ( flgSP == 1 )						   		    	/* 若SP标志为见太阳 */
    {
    	pirawtmp =  ABS( mDSSData.piyaw )  ;

    	if ( pirawtmp > 1.0f )								/* 太敏俯仰测量角 > 1度 */
    	{
        	countPublic++ ;									/* 方式计数器 */

		    if ( countPublic > 12 )    						/* 持续12TS,则太阳搜索完成,转巡航 */
		    {
				TR32_BIAS_WYPI_VALUE( 0.0f ) ;				/* 清俯仰偏置 */

		        /* 转入SAM巡航方式 */
		        TR32_FLGMODE_VALUE(SAM_CRUISE) ;			/* 置巡航方式字 */
		        countMode = 0 ;								/* 清控制周期计数 */
		        countPublic = 0 ;							/* 方式计数器 */
		    }
    	}
	}
    else
    {
        countPublic = 0 ;								     /* 方式计数器 */
    }

    if (countMode > 4500)									 /* 若720秒太阳仍不出现,置ωx=0.5度/秒,ωy=0度/秒,转滚动搜索 */
    {

        TR32_FLGMODE_VALUE(SAM_ROLL) ;						/* 转入SAM滚动搜索方式 */
        TR32_BIAS_WXRO_VALUE(0.5f) ;
        TR32_BIAS_WYPI_VALUE(0.0f) ;

        countMode = 0 ;										/* 控制周期计数器 */
        countPublic = 0 ;									/* 方式计数器 */

    }

	return ;
}

/* 功能：滚动搜索 */
void SAMSubModeRoll(void)
{

    float32 tmproyaw ;

    if (flgSP == 0x1)										/* 若SP=1 */
    {
    	tmproyaw = ABS(mDSSData.royaw) ;

    	if ( tmproyaw > 1.0f )								/* 限幅 */
    	{
        	countPublic++ ;									/* 方式计数器计数 */

        	if (countPublic > 12)							/* 方式计数器13=2.08s 〉2.048s */
        	{

        		TR32_FLGMODE_VALUE(SAM_CRUISE) ;			/* 转入SAM巡航方式 */
        		TR32_BIAS_WXRO_VALUE(0.0f) ;
        		countMode = 0 ;								/* 控制周期计数器 */
        		countPublic = 0 ;							/* 方式计数器清零 */

        	}
    	}
    }
    else
    {
        countPublic = 0 ;									  /* 方式计数器清零 */
    }


    if (countMode > 5000)								    /* 若800s太阳仍不出现,置ωx=0度/秒,ωy=-0.5度/秒,重新俯仰搜索 */
    {

       TR32_FLGMODE_VALUE(SAM_PITCH) ;						/* 转入SAM俯仰搜索方式 */
       TR32_BIAS_WXRO_VALUE(0.0f) ;
       TR32_BIAS_WYPI_VALUE(-0.5f) ;

       countMode = 0 ;										/* 控制周期计数器 */
       countPublic = 0 ;									/* 方式计数器清零 */
    }

	return ;
}

/* 功能：巡航 */
void SAMSubModeCruise(void)
{

	return ;
}

/* 功能：脉冲输出 */
void Pulse_Out(void)
{
	if (Count192ms < 3)                                      /* 脉冲输出时间评后改短 */
	{
		Count192ms++;
	}

	return ;
}

/* 功能：输入陀螺和太敏数据 */
void Input(void)
{
	unint08 si ;
	unint16 wd ;

	/* 读EC模拟量 */
	for ( si=1 ; si<14 ; si++ )
	{

		switch(si)
		{
			case 1:
				mGyroData.wa[8] = DIVIATION_TO_FLOAT_FOG(wd) ;	/* FOG3  当量：9.765625e-4f */

				break ;

			case 2 :
				mGyroData.wa[7] = DIVIATION_TO_FLOAT_FOG(wd) ;	/* FOG2 当量：9.765625e-4f */

				break ;

			case 3:
		 		mGyroData.wa[6] = DIVIATION_TO_FLOAT_FOG(wd) ;	/* FOG1 当量：9.765625e-4f */

				break ;

			case 4:
				mGyroData.wa[5] = DIVIATION_TO_FLOAT_GYRO(wd) ;	/* GYRO6 当量： 1.62760417e-3f  */

				break ;

			case 5:
				mGyroData.wa[4] = DIVIATION_TO_FLOAT_GYRO(wd) ;	/* GYRO5 当量：1.62760417e-3f */

				break ;

			case 6:
				mGyroData.wa[3] = DIVIATION_TO_FLOAT_GYRO(wd) ;	/* GYRO4 当量：1.62760417e-3f */

				break ;

			case 9:
				mGyroData.wa[2] = DIVIATION_TO_FLOAT_GYRO(wd) ;	/* GYRO3 当量：1.62760417e-3f */

				break ;

			case 10:
				mGyroData.wa[1] = DIVIATION_TO_FLOAT_GYRO(wd) ;	/* GYRO2 当量：1.62760417e-3f */

				break ;

			case 11:
				mGyroData.wa[0] = DIVIATION_TO_FLOAT_GYRO(wd) ;	/* GYRO1 当量：1.62760417e-3f */
				break ;

			case 12:
				mDSSData.royaw = DIVIATION_TO_FLOAT_DSS(wd) ;	/* SS1 当量:  2.44140625e-3f */

				break ;

			case 13:
				mDSSData.piyaw = DIVIATION_TO_FLOAT_DSS(wd) ;	/* SS2 当量:  2.44140625e-3f */

				break ;

			default:

				break ;
		}
	}

    return ;
}

/* 功能：陀螺剔野处理 */
void GyroPick(void)
{
    unint08 iy ;
    float32 tmpgi ;

    for ( iy=0 ; iy<9 ; iy++ )
    {

        tmpgi = ABS(mGyroData.wa[iy] - mGyroData.wal[iy]) ;	/* 角度增量剔野处理 */

        if (tmpgi > 0.08f)     								/* 剔野限0.08° */
        {
            mGyroData.countPick[iy]++ ;						/* 野值计数器 */

            if (mGyroData.countPick[iy] < 6)   				/* 没有6次连续野值 */
            {
                mGyroData.wa[iy] = mGyroData.wal[iy] ;		/* 用上周期的值代替本周期的值 */

            }
            else                                			/* 连续6周期野值 */
            {
                mGyroData.wal[iy] = mGyroData.wa[iy] ;		/* 用本周期的值代替上周期的值 */

                mGyroData.countPick[iy] = 0 ;				/* 替代后，野值计数器清零 */

            }
        }
        else                     							/* 没有超出剔野限 */
        {
            mGyroData.wal[iy] = mGyroData.wa[iy] ;			/* 用新值 */

            mGyroData.countPick[iy] = 0 ;					/* 野值计数器清零 */

        }
    }

    return ;

}

/* 功能：陀螺数据处理 */
void GyroProceed(void)
{
    float32 dgi[2] ;

    GyroPick() ;										    /*  B1：剔野 */

    /* B2：计算三轴角速度 */
    GyroChoose() ;											/* 陀螺选择 */
	CalculateGyroRs() ;
    CalculateGyroDg() ;										/* 陀螺三轴角速度计算 */

    /* SAM不进行陀螺漂移补偿 */
    dgi[0] = mGyroData.Gi[0] + mGyroData.W[0] * 0.160f ;	/* 控制周期0.16 */
    dgi[1] = mGyroData.Gi[1] + mGyroData.W[1] * 0.160f ;	/* 控制周期0.16 */

    /* 陀螺角度积分,限在(-180, 180)之间 */
    mGyroData.Gi[0] = ModPNHP(dgi[0], 180.0f) ;				/* 滚动角积分 = 上周期积分总值 + 本周期积分改变值 */
    mGyroData.Gi[1] = ModPNHP(dgi[1], 180.0f) ;			    /* 滚动角积分 = 上周期积分总值 + 本周期积分改变值 */

    return ;
}

/*  功能：选择参加定姿的陀螺 */
void GyroChoose(void)
{
	unint08 i ;									      		/* 循环用临时变量 */

	GyroStateSet() ;									    /* 收集陀螺状态 */

	/* 确定参加工作陀螺的个数 */
	mGyroData.JoinTotal = 0 ;								/* 参加定姿的陀螺个数清零 */
	mGyroData.gyroStatus0 = 0 ;

	for ( i=0 ; i<9 ; i++ )									/* 9个陀螺进行判断 */
	{
		if (mGyroData.StateFlag[i] == TRUE)  				/* 如果陀螺状态正常 */
		{
			mGyroData.SignFlag[mGyroData.JoinTotal] = i ;	/* 统计参加定姿的陀螺螺序号 */
			mGyroData.JoinTotal++ ;							/* 统计参加定姿的陀螺个数 */
			mGyroData.gyroStatus0 = mGyroData.gyroStatus0 | (1 << i) ;
		}

	}

	return ;
}

/* 功能：陀螺状态收集  */
void GyroStateSet(void)
{

	unint08 si ;
	unint16 tmpPS ;
	unint16 tmpHT ;
	unint16 tmpFOGPS ;
	unint16 tmpPSBIT ;
	unint16 tmpHTBIT ;

	for ( si=0 ; si<9 ; si++ )								/* 9个陀螺 */
	{
		tmpPSBIT = tmpPS & (1 << si) ;						/* 找上电 */
		tmpHTBIT = tmpHT & (1 << si) ;						/* 找健康 */

		if ((tmpPSBIT != 0) && (tmpHTBIT == 0))				/* 上电且健康 */
		{
			mGyroData.StateFlag[si] = TRUE ;				/* 陀螺状态标志为正常 */
		}
		else
		{
			mGyroData.StateFlag[si] = FALSE ;				/* 陀螺状态标志为不正常 */
		}
	}

	return ;
}

/* 功能：计算陀螺相关矩阵 */
void CalculateGyroRs(void)
{
	unint08 i ;
 	unint08 j ;
	unint08 k ;
 	float32 Rgtrans[3][5] ;
 	float32 Rs[3][3] ;
	float32 RsInv[3][3] ;
 	float32 Rgtemp[5][3] ;

 	mGyroData.JoinTotal = MIN(mGyroData.JoinTotal, 5) ;

	if (mGyroData.gyroStatus0 != mGyroData.gyroStatus1)		/* 有陀螺切换 */
	{
		for ( j=0 ; j<mGyroData.JoinTotal ; j++ )			/* 参加定姿的陀螺个数 */
		{
			k = mGyroData.SignFlag[j] ;						/* 按从小到大排列依次选5个，不足5个选余下的 */

			for ( i=0 ;  i<3 ; i++ )
			{
				Rgtemp[j][i] = VG[k][i] ;					/* n*3的安装阵R */
			}
		}

		for ( i = mGyroData.JoinTotal ; i<5 ; i++ )			/* 不用的（5-JoinTotal）维，清零 */
		{
			for ( j=0 ; j<3 ; j++ )
			{
				Rgtemp[i][j] = 0.0f;
			}
		}

		if (mGyroData.JoinTotal >= 3)						/* 若大于三个陀螺工作可以计算角速度 */
		{

			MatrixTran(&Rgtrans[0][0], &Rgtemp[0][0], 5, 3) ;					/* Rg->Rgtrans    		*/
			MatrixMulti(&Rs[0][0], &Rgtrans[0][0], &Rgtemp[0][0], 3, 5, 3) ;	/* R*RT->RS       		*/
			MatrixInv33F(&RsInv[0][0], &Rs[0][0]) ;								/* INV(RS)->RsInv 		*/
			MatrixMulti(&mGyroData.Rtemp[0][0], &RsInv[0][0], &Rgtrans[0][0], 3, 3, 5) ;	/* RsInv*Rgtrans->Rtemp */
		}

		mGyroData.gyroStatus1 = mGyroData.gyroStatus0 ;
	}

	return ;
}

/* 功能：计算陀螺三轴角度输出 */
void CalculateGyroDg( void )
{
 	unint08 j ;
	unint08 k ;
	float32 tmpwa[5] ;

	for (j = 0 ; j < 5 ; j++ )	                            /* 给临时数组赋值 */
	{
	     tmpwa[j] = 0 ; 									/* 赋值为0，使用时修改 */
    }
	for ( j=0 ; j<mGyroData.JoinTotal ; j++ )
	{
		k = mGyroData.SignFlag[j] ;							/* 所有参加诊断陀螺的序号 */
		tmpwa[j] = mGyroData.wa[k] ;						/* 取对应序号的模拟量测量值 */
	}

	if ( mGyroData.JoinTotal >= 3 )							/* 若大于三个陀螺工作可定姿 */
	{
		                                                    /* 算角速度 */
		MatrixMulti(&mGyroData.W[0], &mGyroData.Rtemp[0][0], &tmpwa[0], 3, 5, 1) ;

	}
	else
	{
		mGyroData.W[0] = 0.0f ;								/* 参加定姿的陀螺太少 */
		mGyroData.W[1] = 0.0f ;
		mGyroData.W[2] = 0.0f ;
	}

	return ;
}


/* 功能：输入数据处理 */
void Inputproceed(void)
{
	unint08 flgSP ;											/* 硬口读入SP标志 */
    unint08 flgModetmp ;									/* 模式字 */

    flgModetmp = TR32_FLGMODE() ;							/* 方式字 */

	GyroProceed() ;											/* 陀螺数据处理 */

	if ( flgModetmp == SAM_CRUISE )     					/* 巡航方式 */
	{
		if ( flgSP == 1 )   								/* 太阳可见 */
		{
        	mAttitude.angle[0] = mDSSData.royaw ;			/* 滚动角用太敏 */
        	mAttitude.angle[1] = mDSSData.piyaw ;			/* 俯仰角用太敏 */

        	 												/* 将太敏读数替换当前积分值 */
       		 mGyroData.Gi[0] = mDSSData.royaw ;				/* 滚动角陀螺积分  */
       		 mGyroData.Gi[1] = mDSSData.piyaw ;				/* 俯仰角陀螺积分  */
		}
		else												/* 太阳不可见 */
		{
		    mAttitude.angle[0] = mGyroData.Gi[0] ;			/* 滚动角用陀螺积分 */
        	mAttitude.angle[1] = mGyroData.Gi[1] ;			/* 俯仰角用陀螺积分 */
		}
	}

	else    /* 其他模式 */
	{
		mAttitude.angle[0] = 0.0f ;							/* 滚动角清零 */
    	mAttitude.angle[1] = 0.0f ;							/* 俯仰角清零 */
	}


	mAttitude.rate[0] = mGyroData.W[0] ;					/* 滚动角速度用陀螺算出的滚动角速度 */
    mAttitude.rate[1] = mGyroData.W[1] ;					/* 俯仰角速度用陀螺算出的俯仰角速度 */
	mAttitude.rate[2] = mGyroData.W[2] ;					/* 偏航角速度用陀螺算出的偏航角速度 */




	return ;
}

/* 功能：控制器输入限幅 */
void LimitControllerInput(void)
{
    /* 在进行控制器计算前,对输入信号进行限幅 */
    mController[0].Up = mAttitude.angle[0] ;				/* 角度减偏置量，偏置量为0  */
    mController[1].Up = mAttitude.angle[1] ;				/* 角度减偏置量，偏置量为0  */
    mController[2].Up = 0.0f ;								/* Z轴角度清零 */

    mController[0].Ud = mAttitude.rate[0] - TR32_BIAS_WXRO() ;	/* 角速度减偏置量 */
    mController[1].Ud = mAttitude.rate[1] - TR32_BIAS_WYPI() ;	/* 角速度减偏置量 */
    mController[2].Ud = mAttitude.rate[2] ;						/* Z轴角速度无偏置 */

    mController[0].Up = LimitFloat32(mController[0].Up, 8.0f) ;	/* 角度限幅8° */
    mController[1].Up = LimitFloat32(mController[1].Up, 8.0f) ;

    mController[0].Ud = LimitFloat32(mController[0].Ud, 1.2f) ;	/* 角速度限幅1.2° */
    mController[1].Ud = LimitFloat32(mController[1].Ud, 1.2f) ;
    mController[2].Ud = LimitFloat32(mController[2].Ud, 1.2f) ;

    return ;
}

/* 功能：三轴控制器计算 */
void ThreeAxisController(void)
{
	/* 三轴控制器计算 */
    mController[0].fy = mController[0].Up * CTRL_PARAM_SAM[0].Kp + mController[0].Ud * CTRL_PARAM_SAM[0].Kd ;
    mController[1].fy = mController[1].Up * CTRL_PARAM_SAM[1].Kp + mController[1].Ud * CTRL_PARAM_SAM[1].Kd ;
    mController[2].fy = mController[2].Ud * CTRL_PARAM_SAM[2].Kd ;

	/* 控制器输出限幅,伪速率调制器输入,即控制器输出 */
    mModulator[0].u = LimitFloat32(mController[0].fy, 1.3f) ;	/* 伪速率状态量 */
    mModulator[1].u = LimitFloat32(mController[1].fy, 1.3f) ;	/* 伪速率状态量 */
    mModulator[2].u = LimitFloat32(mController[2].fy, 1.3f) ;	/* 伪速率状态量 */

    /* 调用伪速率调制器功能 */
    PseudoRateModulator(&mModulator[0], CTRL_PARAM_SAM[0].h1) ;
    PseudoRateModulator(&mModulator[1], CTRL_PARAM_SAM[1].h1) ;
    PseudoRateModulator(&mModulator[2], CTRL_PARAM_SAM[2].h1) ;

	/* 推力器组合控制逻辑 */
    ThrusterCtrlLogic() ;

	return ;
}

/* 功能：数字伪速率调制器 */
void PseudoRateModulator(SFratemodulator *pModulator, float32 h1)
{
	if ((pModulator->u - pModulator->r) > h1)					/* u(输入)-r（反馈信号）>h1 */
	{
		pModulator->Yp = 0x0 ;									/* 产生32ms正脉冲 */
		pModulator->Yn = 0xF ;
		pModulator->r = 0.9231f * pModulator->r + 0.07688f ;	/*  Y=1 */
	}
	else if ((pModulator->u - pModulator->r) < -h1)				/* u(输入)-r（反馈信号）<h1 */
	{
		pModulator->Yp = 0xF ;									/* 产生32ms负脉冲 */
		pModulator->Yn = 0x0 ;
		pModulator->r = 0.9231f * pModulator->r - 0.07688f ;	/* Y=-1  */
	}
	else														/* 其他 */
	{
		pModulator->Yp = 0x0 ;									/* 不喷 */
		pModulator->Yn = 0x0 ;
		pModulator->r = 0.9231f * pModulator->r ;				/* Y=0  */
	}

	return ;
}

/* 功能：推力器组合逻辑 */
void ThrusterCtrlLogic(void)
{

	if ( mModulator[0].Yp != 0)									/* 伪速率状态量 */
	{
		mThrDistribute.wPulse = mThrDistribute.wPulse | 0x04 ;	/* 软件喷气变量 */
	}

	if ( mModulator[0].Yn != 0)									/* 伪速率状态量 */
	{
		mThrDistribute.wPulse = mThrDistribute.wPulse | 0x08 ;	/* 软件喷气变量 */
	}

	if ( mModulator[1].Yp != 0)									/* 伪速率状态量 */
	{
		mThrDistribute.wPulse = mThrDistribute.wPulse | 0x10 ;	/* 软件喷气变量 */
	}

	if ( mModulator[1].Yn != 0)									/* 伪速率状态量 */
	{
		mThrDistribute.wPulse = mThrDistribute.wPulse | 0x20 ;	/* 软件喷气变量 */
	}

	if ( mModulator[2].Yp != 0)									/* 伪速率状态量 */
	{
		mThrDistribute.wPulse = mThrDistribute.wPulse | 0x40 ;	/* 软件喷气变量 */
	}

	if ( mModulator[2].Yn != 0)									/* 伪速率状态量 */
	{
		mThrDistribute.wPulse = mThrDistribute.wPulse | 0x80 ;	/* 软件喷气变量 */
	}

	return ;
}



/* 功能:限在(-divisor, divisor)之间 */
float32 ModPNHP(float32 x, float32 halfperiod)
{
    float32 period;                                         /* 周期 */
    float32 npp2;                                           /* 限幅后的返回值 */

    /* 计算周期值 */
    period = 2.0f * halfperiod;

    npp2 = x - floor((x + halfperiod) / period) * period;   /* 限幅并返回 */

    return npp2;
}



/* 功能:偏移二进制转换为浮点数 */
float32 DiviationToFloat(unint16 input, unint16 mask, unint16 offset, float32 LSB)
{
    float32 fresult ;		                                /* 局部变量 */

    fresult = ((siint16)((input & mask) - offset)) * LSB ;	/* LSB为最小当量 */

    return fresult ;
}

/* 功能:求三个单精度浮点数中绝对值最大的数 */
float32 TripleFabsMax(float32 fx1, float32 fy2, float32 fz3)
{
    float32 fabsfx1 ;			                            /* 参数1的绝对值 */
    float32 fabsfy2 ;			                            /* 参数2的绝对值 */
    float32 fabsfz3 ;			                            /* 参数3的绝对值 */
    float32 tmax ;				                            /* 最大值 */

    /* 默认为正 */
    fabsfx1 = fx1;                                          /* 赋初值1 */
    fabsfy2 = fy2;                                          /* 赋初值2 */
    fabsfz3 = fz3;                                          /* 赋初值3 */

    /* 取绝对值1 */
    if (fx1 < 0.0f)
    {
        fabsfx1 = -fx1;                                     /* 参数1为负 */
    }

    /* 取绝对值2 */
    if (fy2 < 0.0f)
    {
        fabsfy2 = -fy2;                                     /* 参数2为负 */
    }

    /* 取绝对值3 */
    if (fz3 < 0.0f)
    {
        fabsfz3 = -fz3;                                     /* 参数3为负 */
    }

    /* 求数1与数2绝对值的最大值 */
    if (fabsfx1 > fabsfy2)
    {
        tmax = fabsfx1 ;	                                /* 1绝对值大 */
    }
    else
    {
        tmax = fabsfy2 ;	                                /* 2绝对值大 */
    }

     /* 求数1数2最大值与数3绝对值的最大值 */
    if (fabsfz3 > tmax)
    {
        tmax = fabsfz3 ;	                                /* 3绝对值大 */
    }

    return tmax ;
}

/* 功能:单精度浮点数限幅,要求限幅的阀值fbound大于0 */
float32 LimitFloat32(float32 fin, float32 fbound)
{
    float32 fvalue ;

    if (fin > fbound)
    {
        fvalue = fbound ;
    }
    else if (fin < -fbound)
    {
        fvalue = -fbound ;
    }
    else
    {
        fvalue = fin ;
    }

    return fvalue ;
}

/* 功能:无符号8位整形数的三取二,并回写 */
unint08 Tr32Uint08(unint08 volatile  *pA, unint08 volatile  *pB, unint08 volatile  *pC)
{
    unint08 uitemp1 ;
    unint08 uitemp2 ;
    unint08 uitemp3 ;
    unint08 uiresult ;

    if (((*pA) == (*pB)) && ((*pA) == (*pC)))
    {
        uiresult = (*pA) ;
    }
    else
    {
        uitemp1 = (*pA) & (*pB) ;
        uitemp2 = (*pA) & (*pC) ;
        uitemp3 = (*pB) & (*pC) ;
        uiresult = uitemp1 | uitemp2 | uitemp3 ;

        *pA = uiresult ;
        *pB = uiresult ;
        *pC = uiresult ;
    }

    return uiresult ;
}

/* 功能:无符号32位整形数的三取二,并回写 */
unint32 Tr32Uint(unint32 volatile  *pA, unint32 volatile  *pB, unint32 volatile  *pC)
{
    unint32 uitemp1 ;	                                    /* 1区的值 */
    unint32 uitemp2 ;	                                    /* 2区的值 */
    unint32 uitemp3 ;	                                    /* 3区的值 */
    unint32 uiresult ;	                                    /* 结果 */

     /* 三个数均相等 */
    if (((*pA) == (*pB)) && ((*pA) == (*pC)))               /* 置返回值,取任意一个返回 */
    {
        uiresult = (*pA) ;
    }
    else                                                    /* 不相等 */
    {
        /* 按位三取二 */
        uitemp1 = (*pA) & (*pB) ;		                    /* 两两相与 */
        uitemp2 = (*pA) & (*pC) ;		                    /* 两两相与 */
        uitemp3 = (*pB) & (*pC) ;		                    /* 两两相与 */
        uiresult = uitemp1 | uitemp2 | uitemp3 ;		    /* 结果相或 */

        /* 回写三区 */
        *pA = uiresult ;		                            /* 回写1区 */
        *pB = uiresult ;		                            /* 回写2区 */
        *pC = uiresult ;		                            /* 回写3区 */
    }

    return uiresult ;
}
/* 功能:单精度浮点数的三取二,并回写 */
float32 Tr32Float(float32 volatile  *pA, float32 volatile  *pB, float32 volatile  *pC)
{
    UDTConvert f2ui1 ;
    UDTConvert f2ui2 ;
    UDTConvert f2ui3 ;

    unint32 uitemp1 ;
    unint32 uitemp2 ;
    unint32 uitemp3 ;

    UDTConvert ui2f ;

    f2ui1.flt32 = *pA ;
    f2ui2.flt32 = *pB ;
    f2ui3.flt32 = *pC ;

    uitemp1 = f2ui1.ui32 & f2ui2.ui32 ;
    uitemp2 = f2ui1.ui32 & f2ui3.ui32 ;
    uitemp3 = f2ui2.ui32 & f2ui3.ui32 ;
    ui2f.ui32 = uitemp1 | uitemp2 | uitemp3 ;

    *pA = ui2f.flt32 ;
    *pB = ui2f.flt32 ;
    *pC = ui2f.flt32 ;

    return ui2f.flt32 ;
}


/* 功能:延时 */
void Delay(unint16 delaytime)
{
    unint16 uidt ;

    for ( uidt=0 ; uidt<delaytime ; uidt++ )
    {
       ;
    }

    return ;
}

/* 功能： 矩阵/向量的转置,注意源和目标矩阵/向量不能是同一个 */
void MatrixTran(float32 *tran,
          const float32 *mat,
                unint08 nrow,
                unint08 ncol)
{
	/* 注意源和目标矩阵/向量不能是同一个 */
    unint08 i ;		/* 矩阵行循环变量 */
    unint08 j ;		/* 矩阵列循环变量 */

   /* tran:目标矩阵 */
   /* mat: 源矩阵 */
   /* nrow:矩阵行数 */
   /* ncol:矩阵列数 */

    for ( i=0 ; i<nrow ; i++ )                              /* 行循环 */
    {
        for ( j=0 ; j<ncol ; j++ )                          /* 列循环 */
        {
            *(tran + j * nrow + i) = *(mat + i * ncol + j) ;
        }
    }

    return ;
}

/* 功能：两个矩阵/向量相乘 */
void MatrixMulti(float32 *product,
                 const float32 *faciend,
                 const float32 *multiplier,
                 unint08 nrow,
                 unint08 nrc,
                 unint08 ncol)
{
    unint08 ir ;			                                /* 行循环变量 */
    unint08 jc ;			                                /* 列循环变量 */
    unint08 nk ;			                                /* 求积后做加个数 */
    unint08 index ;			                                /* 矩阵计算结果位置 */

    /* product:求和结果矩阵指针 */
    /* faciend:求和矩阵 */
    /* multiplier:被求和矩阵 */
    /* nrow:矩阵行数 */
    /* nrc:求积后做加个数 */
    /* ncol:矩阵列数 */

    for (ir=0 ; ir<nrow ; ir++)                             /* 行循环 */
    {
        for (jc=0 ; jc<ncol ; jc++)                         /* 列循环 */
        {
            index = ir * ncol + jc ;		                /* 矩阵计算结果位置 */

            product[index] = 0.0f ;			                /* 乘积结果默认取0 */

            for (nk=0 ; nk<nrc ; nk++)                      /* 求积后做加个数循环 */
            {
                product[index] = product[index] + faciend[ir * nrc + nk] * multiplier[nk * ncol + jc] ;
            }
        }
    }

    return ;
}

/***********************************************************************************************
功能：单精度3×3矩阵求逆
***********************************************************************************************/
unint08 MatrixInv33F(float32 *inv, const float32 *src)
{
    siint08 i;
    float32 rank;
    unint08 bAbleInv;   /* TRUE32:矩阵可逆 */

    /* inv:输出结果矩阵指针 */
    /* src:输如计算矩阵指针 */

    /* 默认不可逆 */
    bAbleInv = FALSE32;

    inv[0] = src[4] * src[8] - src[5] * src[7];             /* 第1行第1列 */
    inv[1] = src[2] * src[7] - src[1] * src[8];             /* 第1行第2列 */
    inv[2] = src[1] * src[5] - src[2] * src[4];             /* 第1行第3列 */
    inv[3] = src[5] * src[6] - src[3] * src[8];             /* 第2行第1列 */
    inv[4] = src[0] * src[8] - src[2] * src[6];             /* 第2行第2列 */
    inv[5] = src[2] * src[3] - src[0] * src[5];             /* 第2行第3列 */
    inv[6] = src[3] * src[7] - src[4] * src[6];             /* 第3行第1列 */
    inv[7] = src[1] * src[6] - src[0] * src[7];             /* 第3行第2列 */
    inv[8] = src[0] * src[4] - src[1] * src[3];             /* 第3行第3列 */

    /* 求矩阵的行列式值 */
    rank = src[0] * inv[0] + src[1] * inv[3] + src[2] * inv[6];


    if ((FLT32_ZERO < rank) || (rank < -FLT32_ZERO))         /* 不等于浮点数0 */
    {

        bAbleInv = TRUE32;                                   /* 矩阵可逆 */

        for (i=0; i<9; i++)                                  /* 行列式 */
        {
            inv[i] = inv[i] / rank;
        }
    }
    else
    {
        /* 矩阵不可逆时与原矩阵一致 */
        for (i=0; i<9; i++)
        {
            inv[i] = src[i];
        }
    }

    return bAbleInv;
}


