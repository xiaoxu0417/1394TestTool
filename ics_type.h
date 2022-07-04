/************************************************************************
* 文件名	:ics_type.h
* 
* 创建者	:lzh
*
* 日期		:2019/04/24
* 
* 描述		:定义数据类型
*
* 修改历史(日期/修改者/修改内容):
*
************************************************************************/
#ifndef __ICS_TYPE_H__
#define __ICS_TYPE_H__


/*定义数据类型*/
typedef double					FT64;
typedef float					FT32;
typedef unsigned int			UT32;
typedef signed int				ST32;
typedef unsigned short			UT16;
typedef signed short			ST16;
typedef unsigned char			UT08;
typedef signed char				ST08;
typedef unsigned long long		UT64;
typedef long long				ST64;
#define RIU1_VMC_NDB_DATA_LEN		114
#define RIU2_VMC_NDB_DATA_LEN		114
#define RIU3_VMC_NDB_DATA_LEN		114
#define RIU4_VMC_NDB_DATA_LEN		114
#define VMC_GMP_1_NDB_DATA_LEN      114
#define VMC_GMP_2_NDB_DATA_LEN      114
#define VMC_GMP_3_NDB_DATA_LEN      114
#define VMC_RIU1_NDB_DATA_LEN		50 
#define VMC_RIU2_NDB_DATA_LEN		50 
#define VMC_RIU3_NDB_DATA_LEN		50 
#define VMC_RIU4_NDB_DATA_LEN		50 
#define GMP_VMC_NDB_DATA_LEN		50
#define PIU_BC_VMC_NDB_DATA_LEN		22
#define VMC_FDR_DATA_LEN			114
#define VMC_DEU_DATA_LEN			18
#define VMC_MCPU_DATA_LEN			5
#define MIU_VMC_MS_DATA_LEN			114
#define MIU_VMC_PVI_DATA_LEN		50
#define VMC_GME_FTI_DATA_LEN		92
#define CNT_OF_2S					(2 * 1000/CYC_TIME)

#define Pump_Supply_Start           0//启动供油状态
#define Pump_Supply_Normal          1//正常供油状态
#define VMC_PIU_LEN					18
#define VMC_MIU_1_NDB_DATA_LEN		114
#define VMC_MIU_2_NDB_DATA_LEN		114
#define VMC_MIU_3_NDB_DATA_LEN		114
#define VMC_MFD_DATA_LEN			50
#define VMC_UFCD_DATA_LEN			50
#define STOF_LEN					9
#define AC_Pump_check				6 //422泵检为 6高档
#define DC_Pump_check				1 //直流泵检为 1启动

#define FUELFAST_0_0_0		1
#define FUELFAST_1_0_0		2
#define FUELFAST_0_1_0		3
#define FUELFAST_0_0_1		4
#define FUELFAST_0_1_1		5
#define FUELFAST_1_1_0		6
#define FUELFAST_1_0_1		7
#define FUELFAST_1_1_1		8
#ifndef bool	
//#define bool UT08
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#define CYC_TIME 12.5
#define DURATION(t) t* CYC_TIME
#define DEDURATION(t) ((t*1000)/CYC_TIME)
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
#define OUT_OF_RANGE(v,min1,max1)   ((v)>(max1)) || ((v)<(min1))
#define ONE_IN_RANGE(v,min1,max1)   ((v)>(min1))  && ((v)<(max1))
//#define DEBUG_FOLD
//#define DEBUG_SUPPLY
//#define DEBUG_SAVE
//#define MFL_DEBUG_FAKE_DATA
#define MODIFY_SAVE_20220422
#define MODIFY_AC_0P8_20220523
#define MODIFY_AC_GEAR_20220523
//#define MODIFY_20220424
#define SV_CHECK
#define DEBUG_0728
#define FDR
#define GMP0316 			/*左发、右发任一大于60 则认为当前GMP下发的所有数据均为0，并且当前与GMP通讯故障*/
#define FUEL0316
/*
供油泵档位调节指令:
00H：不工作;    
03H：低档;     
05H：中档;
06H：高档;*/
#define CMD_HIGH_6 6
#define CMD_MID_5 5
#define CMD_LOW_3 3
#define CMD_STOP_0 0

/*直流泵起停控制:
0停止 
1启动
*/
#define DC_CTRL_START_1 1
#define DC_CTRL_STOP_0 0

/*
00：无效    01：打开    10：关闭    11：无效
*/
#define CTRL_INVALID_0 0
#define CTRL_OPEN_1 1
#define CTRL_CLOSE_2 2
#define CTRL_INVALID_3 3

/*
工作状态:
0x00=正常，0x01=故障，0x10=未工作
*/
#define STU_OK_0 0
#define STU_ERR_1 1
#define STU_NOWORK_2 2

/*泵检结果，"00：无效;01：成功;10：失败;11：异常退出"*/
#define CHECK_INVAILD_0 0
#define CHECK_SUCCESS_1 1
#define CHECK_FAILED_2 2
#define CHECK_ERR_3 3

#define CHECK_BEGIN_1 1
#define CHECK_END_2 2

/*信号有效*/
#define VALID_1 1
#define INVALID_0 0

//可控开度阀控制指令(0=关闭 0x01=小开度 0x10=中开度 0x11=大开度,0x100无效,其他无效)
#define OPENING_COLSE_0 0
#define OPENING_SAMLL_1 1
#define OPENING_MID_2 2
#define OPENING_BIG_3 3
#define OPENING_INVAILD_4 4

//AC
//收放指令(00=无效,01=放起落架,10=收起落架,11=无效)
#define CMD_G_INVALID_0 0
#define CMD_G_EXT_1 1
#define CMD_G_RET_2 2
#define CMD_INVALID_3 3

//机翼折叠/展平指令(011-折叠；100-展平；其余无效)
#define CMD_W_FOLD_3 3
#define CMD_W_DIS_4 4
#define CMD_W_INVAILD_0 0

//起落架及舱门状态(00=无效/01=已放下/10=已收上)
#define STU_INVALID_0 0
#define STU_DOWN_1 1
#define STU_UP_2 2

//软件version版本信息
#define VERSION_A 2
#define VERSION_BB 14
#define V_YEAR 22
#define V_MONTH 6
#define V_DAY 6

//油量判断时间:5秒
#define FLOW_TIMER 5000
typedef struct _SOFTWARE_INFO
{
	struct 
	{
		UT32 software_version_A:3;		//软件版本号:A 主版本号
		UT32 software_version_C:5;		//软件版本号:C 1~26对应A~Z
		UT32 software_version_BB:8;		//软件版本号:BB 版本号格式A.B.C
		UT32 bak1:16;		//备份1
	}softwaretype;
	struct
	{
		UT32 year:8;		//软件生成日期:年；数值+2000对应年份
		UT32 month:8;		//软件生成日期:月；1~12
		UT32 day:8;		//软件生成日期:日；1~31
		UT32 bak2:8;		//备份2
	}softwaredate;
}Software_Version;

typedef struct _Software_V
{
	UT32 code					:2;		//成品单位区别码
	UT32 software_version_A		:2;		//软件版本号:A 主版本号0~3
	UT32 software_version_BB	:7;		//软件版本号:BB
	UT32 software_version_C		:5;		//软件版本号:C A~AF,0:A,1:B,11001:Z,11010:AA,11111:AF 版本号格式A.BB.C
	UT32 year					:7;		//软件生成日期:年；数值+2000对应年份
	UT32 month					:4;		//软件生成日期:月；1~12
	UT32 day					:5;		//软件生成日期:日；1~31
}Software_V;

typedef struct _Software_V2
{
	UT32 software_version_A		:3;		//软件版本号:A 主版本号0~3
	UT32 software_version_BB	:8;		//软件版本号:BB
	UT32 software_version_C		:5;		//软件版本号:C A~AF,0:A,1:B,11001:Z,11010:AA,11111:AF 版本号格式A.BB.C
	UT32 year					:7;		//软件生成日期:年；数值+2000对应年份
	UT32 month					:4;		//软件生成日期:月；1~12
	UT32 day					:5;		//软件生成日期:日；1~31
}Software_V2;

/*信号描述*/
typedef struct _FILTERDESC
{
	unsigned int nDelay;		/*滤波周期数*/
	unsigned int nOldStatus;	/*原状态*/
	unsigned int nCycle;		/*信号变化周期*/
	unsigned int nStatus;		/*输出状态*/
}FilterDesc;

/*信号描述*/
typedef struct _FILTER
{
	ST32 nOldStatus;	/*原状态*/
	UT32 nStatus;		/*输出状态*/
}Filter;

/*----------------------------------------------------------------------
描述: 上升沿判断
作者: szy
日期: 2021/04/10
*/
int RisingEdge(FilterDesc* pDesc, unsigned int nStatus);
/*----------------------------------------------------------------------
描述: 下降沿判断
作者: szy
日期: 2021/04/10
*/
int FallingEdge(FilterDesc* pDesc, unsigned int nStatus);
/*----------------------------------------------------------------------
描述: 信号滤波
作者: szy
日期: 2021/04/10
*/
int SignalFilter(FilterDesc* pDesc, unsigned int nStatus);
/*----------------------------------------------------------------------
描述: 信号滤波不包括n->0
作者: szy
日期: 2021/04/10
*/
int SignalFilter_ExcludeZero(FilterDesc* pDesc, unsigned int nStatus);
/*----------------------------------------------------------------------
描述: 选票数据结构
作者: szy
日期: 2021/04/10
*/
typedef struct _VOTE
{
	unsigned int on_ch1		:1;		/*打开/收上1通道值(输入)*/
	unsigned int on_ch2		:1;		/*打开/收上2通道值(输入)*/
	unsigned int off_ch1	:1;		/*关闭/未收上1通道值(输入)*/
	unsigned int off_ch2	:1;		/*关闭/未收上2通道值(输入)*/
	unsigned int on			:1;		/*打开/收上综合值(输出)*/
	unsigned int off		:1;		/*关闭/未收上综合值(输出)*/
	unsigned int on_neq		:1;		/*打开/收上双余度信号不一致(输出)*/
	unsigned int off_neq	:1;		/*关闭/未收上双余度信号不一致(输出)*/
	unsigned int error		:1;		/*错误(输出)*/
	unsigned int :23;
}Vote;
/*----------------------------------------------------------------------
描述: 4判3表决
作者: szy
日期: 2021/04/10
*/
unsigned int Voting(Vote* pVote);

/*
描述: 过滤1位信号,产生变化时输出1;无变化输出0.第一拍输出0
作者: xuzd
日期: 2021/06/10
*/
UT32 filter_XOR(Filter* pDesc, unsigned int nStatus);

#endif
