/* 各型号按照具体情况配置 */
#ifndef  __CONFIG_HEAD__
#define __CONFIG_HEAD__

/******* 编译成电性件还是鉴定件状态 ********/
//#define _DXJ_STATUS_

/* 定义本未卫星编号 */
#define XXT_MARK_SELF	XXT_MARK_KD_01

/* 卫星编号定义 */
#define XXT_MARK_KD_01		0x01
#define XXT_MARK_KD_02		0x02
#define XXT_MARK_KD_03		0x03

#define XXT_MARK_KQ_01		0x41
#define XXT_MARK_KQ_02		0x42
#define XXT_MARK_KQ_03		0x43

#define XXT_MARK_GEO_HZ_01	0x81
#define XXT_MARK_GEO_HZ_02	0x82

#define XXT_MARK_IGSO_ZH_01	0x83
#define XXT_MARK_IGSO_ZH_02	0x84
#define XXT_MARK_IGSO_ZH_03	0x85

#define XXT_MARK_ZHXGZ		0xC1

#define SOFTWARE_VERSION    1.03

/* 宏配置 */
#define   HAVE_GPRS		 0

#if HAVE_GPRS
#define GPRS_NUM           2
#endif

/* 是否配置地敏 1为配置,0为不配置 */
#define   HAVE_ES		 0

/* 是否配置Z轴太敏 1为配置,0为不配置 */
#define   HAVE_DSSZ		0

/* 是否配置加速度计 1为配置,0为不配置 */
#define   HAVE_ACC		 0

/* 是否配置电推 1为配置,0为不配置 */
#define   HAVE_ETTHR	   0

/* 是否配置自主导航 1为配置,0为不配置 */
#define   HAVE_AUTONAVI	0

#if HAVE_AUTONAVI
/* 是否配置GNSS自主导航 1为配置,0为不配置 */
#define   NAVI_GNSS    1

/* 是否配置自校准天文自主导航 1为配置,0为不配置 */
#define   NAVI_SELF_AL    1

/* 是否配置天文自主导航 1为配置,0为不配置 */
#define   NAVI_ASTRO    1

#define NAVI_NUM   NAVI_GNSS+NAVI_SELF_AL+NAVI_ASTRO
#endif


/* 是否计算地影及地影季计算 1为计算,0为不计算 */
#define   HAVE_ECLIPSE	 1

/* 是否为轮控 1为轮控,0为非轮控 */
#define   RW_CTRL		  0

/* 是否为CMG控制 1为CMG控制,0为非CMG控制 */
#define   CMG_CTRL		 0


/* 敏感器数量配置 */
#if HAVE_ES
#define   ES_NUM		   1
#endif

/* 太敏配置个数 */
#define   DSS_XY_NUM	   2

#define   DSS13			0
#define   DSS43			1

#if HAVE_DSSZ
#define   DSS_Z_NUM		0
#endif

/* 星敏复眼配置个数 */
#define STS_NUM			3		
#define STS_SEL_GROUP	6


/* 陀螺配置个数 */
#define   GYRO_NUM		 6

/* 动量轮配置个数 */
#if RW_CTRL
#define   WHEEL_NUM		4
#endif

/* 动量轮配置个数 */
//#if CMG_CTRL
#define   NCmg			 6
//#endif

#if HAVE_ETTHR
#define ET_NUM             4
#endif

/* 推力器喷管配置个数 */
#define   THR_NUM		 14
#define   THR_NUM_A	   7
#define   THR_NUM_B	   7

#define NUM_FOG	  3
#define NUM_HRG	  3
#define NUM_IMU_GYRO 3

#if HAVE_ACC
#define ACC_NUM	  3
#endif

/* 飞行阶段个数，最小为1 */
#define   FLIGHT_PHASE    3

/* 规范化算法配置 */

/* 产品规范配置 */
//#define   _INCLUDE_CSCRIDATASR_          /* 重要数据保存和恢复产品规范 */
#define   _INCLUDE_CSIOCOMDIAG_H_        /* 通信故障诊断产品规范 */

/* 控制周期配置 */
#define TS			0.064

#endif

