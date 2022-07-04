#ifndef _VMC_DEF_H_
#define _VMC_DEF_H_
#include "ics_type.h"
#include <QVariant>
#include <QMetaType>

#pragma pack(push, 1)

#ifndef NULL
//#define NULL 0
#endif

typedef struct  
{
	//00
	UT32 ctrl_stu				:1;//输出状态
	UT32 RIU_err				:1;//RIU与BCUA通道通讯故障
	UT32 break_fault			:1;//刹车故障
	UT32 nslip_err				:1;//防滑
	UT32 off_break_err			:1;//起飞线刹车失效
	UT32 off_break				:1;//起飞线刹车状态==>?
	UT32 drag_break				:1;//牵引刹车状态==>?
	UT32 brake_nslip			:1;//刹车无防滑状态

	UT32 silence_singal			:1;//“静默”模式
	UT32 other_break_err		:1;//另一通道刹车故障
	UT32 break_ctrl_takeoff		:1;//刹车控制开关
	UT32 maintenance_BIT_stu	:1;//维护bit
	UT32						:20;

	//01
	UT32 lsff_ztd_scdl				: 8; /*左伺服阀主通道输出电流*/
	UT32 lsff_btd_scdl				: 8; /*左伺服阀备通道输出电流*/
	UT32 rsff_ztd_scdl				: 8; /*右伺服阀主通道输出电流*/
	UT32 rsff_btd_scdl				: 8; /*右伺服阀备通道输出电流*/

	//02
	UT32 left_wheel_speed	:16;//刹车轮速,左
	UT32 right_wheel_speed	:16;//刹车轮速,右

	//03
	UT32 lbreak_cmd		:16;/*左刹车指令*/
	UT32 rbreak_cmd		:16;/*右刹车指令*/

	//04
	UT32 lbreak_pressure	:16;  //左刹车压力
	UT32 rbreak_pressure	:16;  //右刹车压力
}break_t;

typedef struct  
{
	break_t riu3;
	break_t riu4;
}InputBreak_t;


typedef struct
{
	/*----------64状态字----------*/
	struct
	{
		UT32 break_vd					: 1; /*刹车数据有效*/
		UT32 off_break_err				: 1; /*起飞线刹车失效,RIU3-VMC-DATA1的0052中bit31、RIU4-VMC-DATA1的0052中bit31，同时有效，则报起飞线刹车失效VMC做滤波，滤波周期：250ms*/
		UT32 break_fault				: 1; /*刹车故障,"RIU3-VMC-DATA1的0044中bit12和RIU4-VMC-DATA1的0044中bit12，同时有效，则报刹车故障VMC做滤波，滤波周期：250ms" */
		UT32 nslip_err					: 1; /*防滑故障,"先判断RIU3-VMC-DATA1的0044中bit11“控制输出状态”和RIU4-VMC-DATA1的0044中bit11“控制输出状态”，判断出当前哪个刹车子卡在控制输出；再用当前控制输出的刹车子卡RIU3-VMC-DATA1的0044中bit13或RIU4-VMC-DATA1的0044中bit13，的结果上报防滑故障VMC做滤波，滤波周期：250ms" */
		UT32 maintenance_BIT_stu		: 1; /*维护BIT状态 */
		UT32 off_break					: 1; /*起飞线刹车,"RIU3-VMC-DATA1的0056中bit5和RIU4-VMC-DATA1的0056中bit5，取“或”，判断此状态VMC做滤波，滤波周期：250ms" */
		UT32 drag_break					: 1; /*牵引刹车,"RIU3-VMC-DATA1的0056中bit8和RIU4-VMC-DATA1的0056中bit8，取“或”，判断此状态VMC做滤波，滤波周期：250ms"	*/
		UT32 break_no_nslip				: 1; /*刹车无防滑,"先判断RIU3-VMC-DATA1的0044中bit11“控制输出状态”和RIU4-VMC-DATA1的0044中bit11“控制输出状态”，判断出当前哪个刹车子卡在控制输出；再用当前控制输出的刹车子卡RIU3-VMC-DATA1的0056中bit13或RIU4-VMC-DATA1的0056中bit13，的结果去报刹车无防滑状态VMC做滤波，滤波周期：250ms" */
		UT32 break_down					: 1; /*刹车余度降低,"RIU3-VMC-DATA1的0044中bit12和RIU4-VMC-DATA1的0044中bit12，任意一个有效，则报刹车余度降低VMC做滤波，滤波周期：250ms" */
		UT32 l_break_pres				: 1; /*左刹车有压力, "用于送显的左刹车压力不小于1.5MPa时，此位置有效VMC做滤波，滤波周期：250ms"*/
		UT32 r_break_pres				: 1; /*右刹车有压力, "用于送显的右刹车压力不小于1.5MPa时，此位置有效VMC做滤波，滤波周期：250ms"*/
		UT32 traction_break             : 1; /*11 牵引刹车指令（PIU指令） 0:断开；1：接通*/
		UT32 break_ctrl_takeoff         : 1; /*12 刹车控制（起飞线刹车） 0:断开；1：接通*/
		UT32 break_ctrl_antiskid        : 1; /*13 刹车控制（防滑刹车） 0:断开；1：接通*/
		UT32 break_ctrl_no_antiskid     : 1; /*14 刹车控制（无防滑刹车） 0:断开；1：接通*/
		UT32 back15                     :17; /*15~31 备用 */
	};
	/*----------68状态字----------*/
	struct
	{
		UT32 left_wheel_speed			: 16; /*左轮速度*/
		UT32 right_wheel_speed			: 16; /*右轮速度*/
	};

	/*----------72状态字----------*/
	struct
	{
		UT32 lbreak_cmd					: 16; /*左刹车指令*/
		UT32 rbreak_cmd					: 16; /*右刹车指令*/	
	};

	/*----------76状态字----------*/
	struct
	{
		UT32 lsff_ztd_scdl				: 8; /*左伺服阀主通道输出电流*/
		UT32 lsff_btd_scdl				: 8; /*左伺服阀备通道输出电流*/
		UT32 rsff_ztd_scdl				: 8; /*右伺服阀主通道输出电流*/
		UT32 rsff_btd_scdl				: 8; /*右伺服阀备通道输出电流*/
	};
	/*----------80状态字----------*/
	struct
	{
		UT32 lbreak_pressure			: 16; /*左刹车压力*/
		UT32 rbreak_pressure            : 16; /*右刹车压力*/
	};
}OutputBreak_t;
/*------------------------------------------------------
VMC总输入
*/
typedef struct
{
	//刹车
	InputBreak_t brk;//size 10 int
}Input_vmc;
/*------------------------------------------------------
VMC总输出
*/
typedef struct
{
	//刹车
	OutputBreak_t brk;//size 5 int
}Output_vmc;

Q_DECLARE_METATYPE(OutputBreak_t)
Q_DECLARE_METATYPE(Input_vmc)
Q_DECLARE_METATYPE(Output_vmc)

//extern Input_vmc  g_input;
//extern Output_vmc g_output;

#pragma pack(pop)

#endif
